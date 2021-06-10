#include "ap_int.h"
#include <iostream>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axis <32,1,1,1> AXI_T;
typedef hls::stream<AXI_T> STREAM_T;

int augment(int a){
	a = (a>200)?255:a;
	a = (a>127)&&(a<150)?150:a;
	a = (a<127)&&(a>100)?100:a;
	a = (a<50)?0:a;
	return a;
}

int robert(int a,int b){
    int H1[2][2] = {0,0,0,0};
    int Gx=0, Gy=0;

    H1[0][0] = H1[0][1];H1[0][1] = a;
    H1[1][0] = H1[1][1];H1[1][1] = b;

    Gx = (H1[0][0] - H1[1][1])>0?(H1[0][0] - H1[1][1]):(-(H1[0][0] - H1[1][1]));
    Gy = (H1[0][1] - H1[1][0])>0?(H1[0][1] - H1[1][0]):(-(H1[0][1] - H1[1][0]));

	return (Gx+Gy);
}

void edge_filter(STREAM_T &A, STREAM_T &B, STREAM_T &D, STREAM_T &C,STREAM_T &E, int LEN){
#pragma HLS INTERFACE s_axilite port=LEN bundle=ctrl
#pragma HLS INTERFACE axis port=A
#pragma HLS INTERFACE axis port=B
#pragma HLS INTERFACE axis port=D
#pragma HLS INTERFACE axis port=C
#pragma HLS INTERFACE axis port=E
#pragma HLS INTERFACE s_axilite port=return bundle=ctrl

    AXI_T tmpA, tmpB, tmpC, tmpD, tmpE;

    for(int i=0; i<LEN; i++){
		#pragma HLS unroll factor=32

        A >> tmpA;
        B >> tmpB;
        E >> tmpE;

        tmpC.data = augment(robert(tmpA.data,tmpB.data));
        tmpD.data = augment(robert(tmpB.data,tmpE.data));

        if(i == LEN-1){
            tmpD.last = 1;tmpC.last = 1;
        }else{
            tmpD.last = 0;tmpC.last = 0;
        }
        tmpD.strb = 0xf;tmpC.strb = 0xf;
        tmpD.keep = 0xf;tmpC.keep = 0xf;
        D << tmpD;
        C << tmpC;
    }

}
