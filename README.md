# circularBuffer
This library features a simple header-only C++11 circular buffer implementation which I enjoyed using when developing hardware. As the [Wikipedia entry](https://en.wikipedia.org/wiki/Circular_buffer) for it suggests, circular buffers are useful when storing data streams with a constant amount of memory.

All you need to do to use this library is include the header file `circularBuffer.h` in the root directory and you're set!

## Documentation
DoxyGen documentation for this library is available here. You can also find an example here.

Importantly, it has two write modes. The `CBUF_FILL` write mode stops data storage when the buffer is full as is typical in hardware. However, I've implemented a second write mode `CBUF_OVERWRITE` which overwrites the most stale data in the buffer with the newest data point. This yeilds a sliding window effect on the data stream---this is useful in real-time streaming applications.

## Learning outcomes
This was an interesting two hour-long exercise in converting a hardware/comoputer architecture concept to software. It also helped me refresh my memory of template classes which I use here.