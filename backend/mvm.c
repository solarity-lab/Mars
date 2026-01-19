#include "mvm.h"

struct ProtoFormat* ProtoRunCode(struct ProtoFormat* proto, Instruction *bytecode, MarsSize size) {
    Instruction op = bytecode[proto->pc];

    proto->labels = ProgramSetLabel(bytecode, size);

    GCActivate(proto->gc);

    for (;;) {
        op = bytecode[proto->pc];

        if (op == OKHALT) break;

        switch (op) {
            case OKADD: ProtoAdd(proto); break;
            case OKSUB: ProtoSub(proto); break;
            case OKDIV: ProtoDiv(proto); break;
            case OKMUL: ProtoMul(proto); break;
            case OKMOD: ProtoMod(proto); break;

            case OKGT:  ProtoCompare(proto, OKGT);  break;
            case OKGTE: ProtoCompare(proto, OKGTE); break;
            case OKLT:  ProtoCompare(proto, OKLT);  break;
            case OKLTE: ProtoCompare(proto, OKLTE); break;
            case OKEQ:  ProtoCompare(proto, OKEQ);  break;
            case OKNEQ: ProtoCompare(proto, OKNEQ); break;

            case OKPUSH_NUM: {
                uint8_t b[4];
                b[0] = bytecode[++proto->pc];
                b[1] = bytecode[++proto->pc];
                b[2] = bytecode[++proto->pc];
                b[3] = bytecode[++proto->pc];

                float value;
                memcpy(&value, b, sizeof(float));

                ProtoPushNum(proto, value);

                break;
            }
            case OKPRINT: {
                struct Object* value = ProtoStackTake(proto);
                printf("%g\n", value->value);

                GCmove(proto->gc, value);
                break;
            }

            case OKLOAD: {
                address_t address = bytecode[++proto->pc];
                struct Object* value = ProtoLoadGlobal(proto, address);
                
                ProtoStackPush(proto, value->f_value);

                break;
            }

            case OKLOAD_LOCAL: {
                address_t address = bytecode[++proto->pc];
                struct Object* value = ProtoLoadLocal(proto, address);

                ProtoStackPush(proto, value->f_value);
                
                break;
            }

            case OKSTORE: {
                address_t address = bytecode[++proto->pc];
                struct Object* value = ProtoStackTake(proto);
                
                ProtoStoreGlobal(proto, address, value, O_GLOBAL);

                break;
            }

            case OKSTORE_LOCAL: {
                address_t address = bytecode[++proto->pc];
                struct Object* value = ProtoStackTake(proto);

                ProtoStoreLocal(proto, address, value, O_LOCAL);

                break;
            }

            case OKPOP: ProtoStackPop(proto); break;

            case OKADDRESS: proto->pc++; break;

            case OKJMP: {
                address_t address = bytecode[++proto->pc];
                struct Label label = ProgramGetLabel(proto->labels, address);

                proto->pc = label.offset;
                break;
            }

            case OKJMP_IF_FALSE: {
                address_t address = bytecode[++proto->pc];
                struct Label label = ProgramGetLabel(proto->labels, address);

                struct Object* value = ProtoStackTake(proto);

                if (!value->value) {
                    proto->pc = label.offset;
                }

                GCmove(proto->gc, value);

                break;
            }

            case CCCREATE: {
                struct Object* height = ProtoStackTake(proto);
                struct Object* width = ProtoStackTake(proto);

                int height_value = height->value;
                int width_value = width->value;

                struct Grid* grid = GridCreate(width_value, height_value);

                proto->grid = grid;

                GCmove(proto->gc, height);
                GCmove(proto->gc, width);
                
                break;
            }

            case CCREAD: {
                struct Grid* grid = proto->grid;

                if (grid) {
                    GridPrint(grid);
                }
                break;
            }

            case CCCLOSE: {
                struct Grid* grid = proto->grid;

                if (grid) {
                    GridFree(grid);
                    proto->grid = NULL;
                }
                break;
            }

            case CCMOVE_TO: {
                struct Object* column = ProtoStackTake(proto);
                struct Object* row = ProtoStackTake(proto);

                int row_index = row->value;
                int col_index = column->value;

                if (proto->grid) CursorMoveTo(proto->grid->cursor, row_index, col_index);

                GCmove(proto->gc, column);
                GCmove(proto->gc, row);
                
                break;
            }

            case CCWRITE: {
                struct Object* value = ProtoStackTake(proto);

                if (proto->grid) ProtoGridWrite(proto, value);

                GCmove(proto->gc, value);

                break;
            }

            case OKHALT: break;
        }
        
        proto->pc++;

        GCStartClean(proto->gc);
    }

    GCDeactivate(proto->gc);

    return proto;
}