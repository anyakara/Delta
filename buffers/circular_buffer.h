#ifndef __RING_BUFFER_
#define __RING_BUFFER_

#include <cstddef>
#include <cstdint>

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    size_t count;
    size_t high_priority_count;
    uint8_t *buffer;
    uint8_t *priority_buffer;
} CircularBuffer;

// initialize advanced buffer
bool advanced_buffer_init(CircularBuffer *acb, uint8_t *buffer, uint8_t *priority_buffer, size_t size) {
    if (!acb || !buffer || !priority_buffer || size == 0) return false;
    acb->buffer = buffer;
    acb->priority_buffer = priority_buffer;
    acb->size = size;
    acb->head = acb->tail = acb->count = acb->high_priority_count = 0;
    return true;
};

// write with priority
bool advanced_buffer_write(CircularBuffer *acb, uint8_t data, bool high_priority) {
    if (high_priority) {
        if (acb->high_priority_count == acb->size) return false;
        acb->priority_buffer[acb->high_priority_count++] = data;
    } else {
        if (acb->count == acb->size) return false;
        acb->buffer[acb->head] = data;
        acb->head= (acb->head + 1) % acb->size;
        acb->count++;
    } return true;
};


// batch read sensor input
size_t advanced_buffer_batch_read(CircularBuffer *acb, uint8_t *output, size_t max_elements) {
    size_t read_count = 0;
    while (read_count < max_elements && acb->count > 0) {
        output[read_count++] = acb->buffer[acb->tail];
        acb->tail = (acb->tail + 1) % acb->size;
        acb->count--;
    } return read_count;
};

#endif // __CIRCULAR_BUFFER_