# Image_Filter_Xilinx
Design of Image filter using synchronized data streaming from DMA in Zynq FPGA board using Pynq framework

# Streaming using DMA
The DMAs used for streaming data from CPU to CLBs of our FPGA can be multiplied in design to achieve much higher parallelism

# Pros and Cons
Since streaming is a bit slower for images (reading images as an array from memory is faster becuase we can use loop unrolling in Xilinx fpga) but the principle of this design has other applicaions which can work best with streaming interfaces.

# Application
Multiagent bot control using faster continous data processing
Filter with continous data streams, Converters and Controllers in electronic devices
