#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
#include "openrtb_2_3.h"

#define ORTB_LOG(format, ...); fprintf(stderr, "ORTB_LOG|%s:%d|"format \
		"\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define ORTB_ERROR(format, ...); fprintf(stderr, "ORTB_ERR|%s:%d|"format \
		"\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define JSON_CHECK_FOR_NULL(obj, format, ...) \
	if (NULL == obj) { \
		ORTB_ERROR(format, ##__VA_ARGS__); \
		break; \
	}

int json_copy_string(char **dst, struct json_object* obj) {
	int len = 0;
	*dst = NULL;

	len = json_object_get_string_len(obj);
	
	if (len > 0) {
<<<<<<< HEAD
		*dst = (char*) malloc(sizeof(char) * (len + 1));
=======
		len += 1; 
		*dst = (char*) malloc(sizeof(char) * len);
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
		if (NULL == *dst) {
			ORTB_ERROR("NO MEMORY AVAILABLE");
			return NO_MEMORY;
		}
	
		strncpy(*dst, json_object_get_string(obj), len);
<<<<<<< HEAD
		(*dst)[len] = 0;
=======
		*dst[len] = 0;
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
	}

	return COPY_SUCCESS;
}

int json_copy_string_array(char ***array, int *nsize, struct json_object* obj) {
	int idx = 0;
	int len = 0;
	char **temp;
	char *ele;

	*array = NULL;
	*nsize = 0;
	len = json_object_array_length(obj);
	if (len > 0) {
		temp = (char **) malloc(sizeof(char) * len);
		if (NULL == temp) {
			ORTB_ERROR("NO MEMORY AVAILABLE");
			return NO_MEMORY;
		}
		
		for(idx = 0; idx < len; idx++) {
			json_object* val = json_object_array_get_idx(obj, idx);
			ele = NULL;
			json_copy_string(&ele, val);
			temp[idx] = ele;
		}

		*array = temp;
		*nsize = len;
	}

	return COPY_SUCCESS;
}

void freeBidRequest(BidRequest *bidRequest) {
	do{
		if (NULL == bidRequest)
			break;

		if (NULL != bidRequest->id)
			free(bidRequest->id);


	}while(0);
	
	return;
}

int initBidRequestDefaultValues(BidRequest *bidRequest) {
	do {
		if (NULL == bidRequest)
			break;
		
		if (0 == bidRequest->at)
			bidRequest->at = 2; // 2 is for Second Price Plus

		if (0 == bidRequest->at)
			bidRequest->test = 0; // 1 is for live, 0 for live
	}while(0);
}

int parseBidRequest(json_object* root, BidRequest *bidRequest) {
	int retval = PARSE_FAILED;
	int vallen = 0;
	json_object_object_foreach(root, key, val) {
		ORTB_LOG("parseBidRequest:key:%s", key);
		do {
			if (NULL == val) {
				ORTB_LOG("NULL value found for key: %s", key);
				continue;
			}

			if (!strcmp(ORTB_ID, key)) {
				if(COPY_SUCCESS != json_copy_string(&bidRequest->id, val)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_ID);
						return retval;
				}

				break;
			}
			
			if (!strcmp(ORTB_TEST, key)) {
				bidRequest->test = json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_AT, key)) {
				bidRequest->at = json_object_get_int(val);
				break;
			}
			
			if (!strcmp(ORTB_TMAX, key)) {
				bidRequest->tmax = json_object_get_int(val);
				break;
			}
<<<<<<< HEAD
		
=======
			
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
			if (!strcmp(ORTB_WSEAT, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&bidRequest->wseat, &bidRequest->nwseat, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_WSEAT);
					return retval;
				}
				break;
			}
			
			if (!strcmp(ORTB_ALLIMPS, key)) {
				bidRequest->allimps = json_object_get_int(val);
				break;
			}
			
			if (!strcmp(ORTB_CUR, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&bidRequest->cur, &bidRequest->ncur, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_CUR);
					return retval;
				}
				break;
			}
<<<<<<< HEAD
			
=======
		/*	
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
			if (!strcmp(ORTB_BCAT, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&bidRequest->bcat, &bidRequest->nbcat, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_BCAT);
					return retval;
				}
				break;
			}
			
			if (!strcmp(ORTB_BADV, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&bidRequest->badv, &bidRequest->nbadv, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_BADV);
					return retval;
				}
				break;
			}
<<<<<<< HEAD
			
=======
			*/
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
			ORTB_ERROR("Invalid key in BidRequest: key: %s", key);
		}while(0);
	}

	retval = PARSE_SUCCESS;

	return retval;
}

int parseRequest(const char* src, BidRequest *bidRequest) {
	ORTB_LOG("In parse. parsing bid request object...");
	json_object* root = json_tokener_parse(src);
	int retval = PARSE_FAILED; 
	do{
		JSON_CHECK_FOR_NULL(root, "Invalid input json: %s", src);

		if (PARSE_SUCCESS != parseBidRequest(root, bidRequest))
				break;
	
		retval = PARSE_SUCCESS;
		ORTB_LOG("parsing bid request object completed.");
	}while(0);

	// free the allocated json-c lib memory
	json_object_put(root);

	return retval;
}
