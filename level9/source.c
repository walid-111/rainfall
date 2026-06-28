void __thiscall N::setAnnotation(N *this,char *param_1)
{
  size_t __n;
  
  __n = strlen(param_1);
  memcpy(this + 4,param_1,__n);
  return;
}


typedef struct struct_1 {
    struct struct_0 *field_0;
} struct_1;

typedef struct struct_2 {
    char padding_0[4];
    char *field_4;
} struct_2;

typedef struct struct_0 {
    unsigned int field_0;
} struct_0;

int main(int a0, struct_2 *a1)
{
    unsigned int v5;  // ebx
    struct_1 **v6;  // ebx
    unsigned int v0;  // [bp-0x20]
    struct_1 **v1;  // [bp-0x18]
    unsigned int v2;  // [bp-0x14]
    struct_1 **v3;  // [bp-0x10]
    unsigned int v4;  // [bp-0xc]

    if (a0 > 1)
    {
        v5 = operatornew(108);
        N::N(v5, 5);
        v4 = v5;
        v6 = operatornew(108);
        N::N(v6, 6);
        v3 = v6;
        v2 = v4;
        v1 = v3;
        N::setAnnotation(v2, a1->field_4);
        return *(v1)->field_0(v1, v2, v0);
    }
    _exit(1); /* do not return */
}