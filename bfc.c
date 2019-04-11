#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"Usage: bfc <code>\n");
        return 1;
    }

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("    mov esi, 1\n");
    printf("    mov edi, 30000\n");
    printf("    call calloc\n");
    printf("    mov rbx, rax\n");
    printf("    mov r12, 0\n");

    char* p = argv[1];
    int *loop = (int*)malloc(sizeof(int)*256);
    int loop_id = 0;

    while(*p){
        // printf("%d\n",*p);
        switch (*p++)
        {
            case '+':
                printf("    lea rax, [rbx + r12]\n");
                printf("    inc BYTE PTR [rax]\n");
                break;
            case '-':
                printf("    lea rax, [rbx + r12]\n");
                printf("    dec BYTE PTR [rax]\n");
                break;
            case '>':
                printf("    inc r12\n");
                break;
            case '<':
                printf("    dec r12\n");
                break;
            case '.':
                printf("    lea rax, [rbx + r12]\n");
                printf("    movzx edi, BYTE PTR [rax]\n");
                printf("    movsx edi, di\n");
                printf("    call putchar\n");
                break;
            case ',':
                printf("    call getchar\n");
                printf("    mov edx, eax\n");
                printf("    lea rax, [rbx + r12]\n");
                printf("    movzx BYTE PTR [rax], dl\n");
                break;
            case '[':
                *(++loop) = loop_id++;
                printf(".L%d:\n", *loop);
                break;
            case ']':
                printf("    lea rax, [rbx + r12]\n");
                printf("    movzx eax, BYTE PTR [rax]\n");
                printf("    test al,al\n");
                printf("    jne .L%d\n",*(loop--));
                break;
            default:
                break;
        }
    }
    
    printf("    mov rax, 0\n");
    printf("    ret\n");
    return 0;
}
