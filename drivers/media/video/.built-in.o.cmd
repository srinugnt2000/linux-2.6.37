cmd_drivers/media/video/built-in.o :=  arm-none-linux-gnueabi-ld -EL    -r -o drivers/media/video/built-in.o drivers/media/video/videodev.o drivers/media/video/v4l2-int-device.o drivers/media/video/v4l2-common.o drivers/media/video/v4l1-compat.o drivers/media/video/videobuf-core.o drivers/media/video/videobuf-dma-contig.o drivers/media/video/davinci/built-in.o drivers/media/video/uvc/built-in.o drivers/media/video/ir-kbd-i2c.o 
