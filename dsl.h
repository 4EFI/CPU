#ifndef DSL_H
#define DSL_h

//-----------------------------------------------------------------------------

#define S_POP         StackPop ( &cpu->stack )
#define S_PUSH( VAL ) StackPush( &cpu->stack, VAL )

#define S_RET_POP         StackPop ( &cpu->stkRetIP )
#define S_RET_PUSH( VAL ) StackPush( &cpu->stkRetIP, VAL )

#define ASM_PUT_CODE( VAL, IP )                          \
    memcpy( asm_s->code + *IP, &VAL, sizeof( Elem_t ) ); \
    (*IP) += sizeof( Elem_t );   

//-----------------------------------------------------------------------------
    
#endif 