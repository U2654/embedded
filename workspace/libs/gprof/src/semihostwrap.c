/* added for using with gdb and jlinkgdbserver by U2654 matt */
#ifndef OPENOCD

#define SEMIHOSTING_SYS_CLOSE 0x02
#define SEMIHOSTING_SYS_OPEN  0x01
#define SEMIHOSTING_SYS_WRITE 0x05

typedef void* field_t ;
static char filename[128];
static char* buffer = 0;
static volatile unsigned int buffersize;

int os_semihosting_call_host (int reason, void* arg)
{
    field_t* fields = (field_t*) arg;
    if (reason == SEMIHOSTING_SYS_OPEN )
    {
        const char* path = (const char*) fields[0];
        strcpy(filename, path);
        buffersize = 0;
        return 1;
    }
    else if(reason == SEMIHOSTING_SYS_CLOSE)
    {
/* set breakpoint here */
/* write out profiling data now with debugger: */
/* dump binary memory gmon.out buffer buffer+buffersize */
        free(buffer);
        buffersize = 0;
        return 0;   
    }
    else if (reason == SEMIHOSTING_SYS_WRITE)
    {
        unsigned int chunksize = (unsigned int) fields[2];
        buffer = realloc(buffer, buffersize+chunksize);
        memcpy(buffer+buffersize, fields[1], chunksize);
        buffersize += chunksize;
        return 0;
    }
    // else not supported
    return reason;
}

#endif