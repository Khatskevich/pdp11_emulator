R0-width/height of display
R1-current width
R2-current height
R3-source addr
R4-dst addr
R5 = R0-R1


for(y=-heidgt_curr;y<0;y++){
	for(x=-width_curr;x<0;x++){
		*dst=*src;
		dst++;
		src++;
	}
	dst+=(height-height_curr)
}

		MOV -HEIGHT, R2
		MOV SOURCE_ADDR, R3
		MOV DEST_ADDR, R4
		MOV -R1, R5
		ADD R0, R5
XLOOP1:	MOV -WIDTH, R1
XLOOP2:	MOV (R3)+, (R4)+
		INC R1
		BNE XLOOP2
		ADD R5, R4
		INC R2
		BNE XLOOP1
		EXIT





