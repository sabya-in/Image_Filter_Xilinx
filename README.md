# Image_Filter_Xilinx
Design of Image filter using synchronized data streaming from DMA in Zynq FPGA board using Pynq framework

# Streaming using DMA
1. The DMAs used for streaming data from CPU to CLBs of our FPGA can be cloned in design to achieve much higher parallelism.
2. Each DMA is used to stream row wise pixels into our Kernel / processing unit, which would mean data can be continously received and stored (DMA should make it faster).
3. Each Kernel using loop unrolling for each individual stream to make them faster.

# Pros and Cons
Since streaming is a bit slower for images (reading images as an array from memory is faster becuase we can use loop unrolling in Xilinx fpga) but the principle of this design has other applicaions which can work best with streaming interfaces.

# Application
1. Multiagent bot control using faster continous data processing
2. Filter with continous data streams
3. Converters and Controllers in electronic devices
       
