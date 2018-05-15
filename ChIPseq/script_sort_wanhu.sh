#!/bin/bash

INPUT_NAME[0]=GA8161
INPUT_NAME[1]=GA8162
INPUT_NAME[2]=GA8166
INPUT_NAME[3]=GA8167

INPUT_DIR[0]=zhangyi_data
INPUT_DIR[1]=zhangyi_data
INPUT_DIR[2]=zhangyi_data
INPUT_DIR[3]=zhangyi_data

OUTPUT_DIR=zhangyi_data
FNAME2=H2AZ_GA8162_GA8166_shLuc_shH2AZ_neg

FILE_INPUT[0]=${INPUT_NAME[0]}_hg18_no_input_peaks_with_peak_pos_sorted.txt
FILE_INPUT[1]=${INPUT_NAME[1]}_hg18_no_input_peaks_with_peak_pos_sorted.txt
FILE_INPUT[2]=${INPUT_NAME[2]}_hg18_no_input_peaks_with_peak_pos_sorted.txt
FILE_INPUT[3]=${INPUT_NAME[2]}_hg18_no_input_peaks_with_peak_pos_sorted.txt



cat ./${INPUT_DIR[0]}/${FILE_INPUT[0]} ./${INPUT_DIR[1]}/${FILE_INPUT[1]} ./${INPUT_DIR[2]}/${FILE_INPUT[2]} ./${INPUT_DIR[3]}/${FILE_INPUT[3]}>./${OUTPUT_DIR}/${FNAME2}_macs_no_input_peaks_combined_peaks_2.txt

sort -k2,2 -k3g,3<./${OUTPUT_DIR}/${FNAME2}_macs_no_input_peaks_combined_peaks_2.txt>./${OUTPUT_DIR}/${FNAME2}_macs_no_input_peaks_combined_peaks_sorted_2.txt




