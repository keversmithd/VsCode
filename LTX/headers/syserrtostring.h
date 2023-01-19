#include <iostream>

const char* errbuffer_path = "errbuffer.txt";


size_t syserrfilesize(FILE* errbuffer)
{
    if(errbuffer != NULL)
    {
        fpos_t s = 0,e = 0;
        fseek(errbuffer, 0, SEEK_SET);
        fgetpos(errbuffer, &s);
        fseek(errbuffer, 0, SEEK_END);
        fgetpos(errbuffer, &e);
        return (size_t)(e - s);
    }
    return 0;
    

}

void reallocerrorstring(char* errbuffer_ptr, size_t currentsize)
{
    FILE* errbuffer = fopen(errbuffer_path, "rb");

    if(errbuffer == NULL || errbuffer_ptr == nullptr)
    {
        printf("%s, %d, %s \n" "Error buffer was null. Error\n", __LINE__);
        return;
    }

    size_t errbuffersize = syserrfilesize(errbuffer);

    if(errbuffersize > currentsize)
    {
        void* reallocstatus = realloc(errbuffer_ptr, errbuffersize);
        if(reallocstatus == nullptr)
        {
            printf("%s, %d, %s \n" "Memory error reallocating in reallocerrorstring: Error\n", __LINE__);
        }

    }

    return;
}

void syserrtofile(const char* cmd)
{
    
    FILE* errbuffer = freopen(errbuffer_path, "w", stderr);
    fseek(errbuffer, 0, SEEK_SET);
    system(cmd);
    freopen("CONOUT$", "w", stderr);
    system(cmd);
    fclose(errbuffer);
}
