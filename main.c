#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* call2bash(char* cmd) {
    FILE *fp;
    char res[8096];
    char buffer[80];
    fp = popen(cmd, "r");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // printf("%s", buffer);
        strcat(res, buffer);
    }
    pclose(fp);
    return res;
}

void buildAndRunInC(char* input) {
    FILE *fp, *file;

    file = fopen("tmp/test.c", "w+");
    if (file == NULL) {
        printf("not created tmp/test.c");
    }
    fprintf(file, input);
    fclose(file);
}

int main() {
    buildAndRunInC("#include<stdio.h>\nint main() {\n\tprintf(\"Hello World\");\n\treturn 0;\n}");
    call2bash("gcc -o test ./tmp/test.c");
    char *res = call2bash("./test");
    printf("%s\n", res);
    return 0;
}