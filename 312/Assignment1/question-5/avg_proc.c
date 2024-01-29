#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>

static double length; 

input_data* average_1(input_data *input, CLIENT *client) {
  // Declare variables
  static input_data sorted_data; 
  int i, j; 
  length = input->input_data.input_data_len; 

  // Place values inputted into another input_data struct 
  sorted_data.input_data = input->input_data;
	for(i = 0; i < length; i++){
		sorted_data.input_data.input_data_val[i] = input->input_data.input_data_val[i];
	}

  // Iterate through data and switch location if value next to current is smaller using temp array
	for(i = 0; i < length; i++){
		for(j = i + 1; j < length; j++){
			if(sorted_data.input_data.input_data_val[i] > sorted_data.input_data.input_data_val[j]){
				double temp  = sorted_data.input_data.input_data_val[i];
				sorted_data.input_data.input_data_val[i] = sorted_data.input_data.input_data_val[j];
				sorted_data.input_data.input_data_val[j] = temp;
			}
		}
	}

  return(&sorted_data);
}

input_data* average_1_svc(input_data *input, struct svc_req *svc) {
    CLIENT *client;
    return(average_1(input, client));
}

