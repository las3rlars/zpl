#define ZPL_IMPLEMENTATION
#include <zpl.h>

void test_read_finished(zpl_async_file *file) {
    zpl_file_close(&file->handle);
    zpl_sleep_ms(1000);
    zpl_printf("Size: %d\n", cast(int)file->size);
}

void test_write_finished(zpl_async_file *file) {
    zpl_file_close(&file->handle);
    zpl_sleep_ms(1000);
    zpl_printf("Size: %d\n", cast(int)file->size);
    
    zpl_mfree(file->data); // user is responsible for the original data.
}

int main() {
    zpl_file test_file = {0};
    
    zpl_file_open(&test_file, "../include/zpl.h");
    {
        zpl_async_file_read(&test_file, test_read_finished);
        zpl_printf("We should read at this moment!\n");
    }
    
    zpl_sleep_ms(3000);
    
    zpl_file write_file = {0};
    
    zpl_file_create(&write_file, "test.txt");
    {
        char *buf = (char *)zpl_malloc(64); // arbitrary sized heap-allocated buffer.
        for (int i = 0; i < 64; i++) if (i % 2 == 0) buf[i] = '0'; else buf[i] = '1';
        zpl_async_file_write(&write_file, (void *)buf, 64, test_write_finished);
        zpl_printf("We should write at this moment!\n");
    }
    
    zpl_sleep_ms(3000);
    
    return 0;
}
