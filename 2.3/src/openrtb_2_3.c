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

#define FREE_AND_RESET(obj) \
	if (NULL != obj) { \
		free(obj); \
		obj = NULL; \
	}

#define FREE_AND_RESET_LIST(nitem, item) \
	if (nitem > 0) { \
		for(;nitem > 0; nitem--) { \
			free(item[nitem-1]); \
			item[nitem-1] = NULL; \
		} \
		free(item); \
		item == NULL; \
	}


int json_copy_string(char **dst, struct json_object* obj) {
	int len = 0;
	*dst = NULL;

	if (NULL == obj)
		return COPY_SUCCESS;

	len = json_object_get_string_len(obj);
	
	if (len > 0) {
		*dst = (char*) malloc(sizeof(char) * (len + 1));
		if (NULL == *dst) {
			ORTB_ERROR("NO MEMORY AVAILABLE");
			return NO_MEMORY_AVAILABLE;
		}
	
		strncpy(*dst, json_object_get_string(obj), len);
		(*dst)[len] = 0;
	}

	return COPY_SUCCESS;
}

int json_copy_int_array(int **array, int *nsize, struct json_object* obj) {
	int idx = 0;
	int len = 0;
	int* temp;

	*array = NULL;
	*nsize = 0;

	if (NULL == obj)
		return COPY_SUCCESS;

	len = json_object_array_length(obj);

	if (len > 0) {
		temp = (int*) malloc(sizeof(int) * len);
		if (NULL == temp) {
			ORTB_ERROR("NO MEMORY AVAILABLE");
			return NO_MEMORY_AVAILABLE;
		}

		int nelement = 0;
		for(idx = 0; idx < len; idx++) {
			json_object* val = json_object_array_get_idx(obj, idx);
			
			if (NULL == val)
				continue;

			temp[nelement] = json_object_get_int(val);
			nelement++;
		}

		*array = temp;
		*nsize = nelement;
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
	
	if (NULL == obj)
		return COPY_SUCCESS;
	
	len = json_object_array_length(obj);
	if (len > 0) {
		temp = (char **) malloc(sizeof(char) * len);
		if (NULL == temp) {
			ORTB_ERROR("NO MEMORY AVAILABLE");
			return NO_MEMORY_AVAILABLE;
		}

		int nelement = 0;
		for(idx = 0; idx < len; idx++) {
			json_object* val = json_object_array_get_idx(obj, idx);
			
			if (NULL == val)
				continue;

			ele = NULL;
			json_copy_string(&ele, val);
			temp[nelement] = ele;
			nelement++;
		}

		*array = temp;
		*nsize = nelement;
	}

	return COPY_SUCCESS;
}

void freeBidRequest(BidRequest *bidRequest) {
	do{
		if (NULL == bidRequest)
			break;

		FREE_AND_RESET(bidRequest->id);
		FREE_AND_RESET_LIST(bidRequest->nwseat, bidRequest->wseat);	
		FREE_AND_RESET_LIST(bidRequest->ncur, bidRequest->cur);	

		FREE_AND_RESET_LIST(bidRequest->nbcat, bidRequest->bcat);	
		FREE_AND_RESET_LIST(bidRequest->nbadv, bidRequest->badv);	
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

int parseBanner(json_object* bannerObj, Impression *imp) {
	ORTB_LOG("In parseBanner()");
	int retval = PARSE_FAILED;
	if (NULL == bannerObj) {
		ORTB_ERROR("Banner object is absent in bidrequest");
		return retval;
	}

	// Allocate memory for Banner objects.
	imp->banner = (Banner *) malloc(sizeof(Banner));
	Banner *banner = imp->banner;
	int nelement = 0;
	json_object_object_foreach(bannerObj, key, val) {
		ORTB_LOG("parseBannerObj:key:%s", key);
		do {
			if (NULL == val) {
				ORTB_LOG("NULL value found for key: %s", key);
				continue;
			}

			if (!strcmp(ORTB_ID, key)) {
				if(COPY_SUCCESS != json_copy_string(&banner->id, val)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_ID);
						return retval;
				}

				break;
			}
		
			if (!strcmp(ORTB_W, key)) {
				banner->w= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_H, key)) {
				banner->h= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_WMAX, key)) {
				banner->wmax= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_HMAX, key)) {
				banner->hmax= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_WMIN, key)) {
				banner->wmin= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_HMIN, key)) {
				banner->hmin= json_object_get_int(val);
				break;
			}

			if (!strcmp(ORTB_POS, key)) {
				banner->pos = json_object_get_int(val);
				break;
			}
			
			if (!strcmp(ORTB_TOPFRAME, key)) {
				banner->topframe = json_object_get_int(val);
				break;
			}
			
			if (!strcmp(ORTB_MIMES, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&banner->mimes, &banner->nmimes, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_MIMES);
					return retval;
				}
				break;
			}
			
			if (!strcmp(ORTB_BTYPE, key)) {
				if(COPY_SUCCESS != json_copy_int_array(&banner->btype, &banner->nbtype, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_BTYPE);
					return retval;
				}
				break;
			}

			if (!strcmp(ORTB_BATTR, key)) {
				if(COPY_SUCCESS != json_copy_int_array(&banner->battr, &banner->nbattr, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_BATTR);
					return retval;
				}
				break;
			}

			if (!strcmp(ORTB_EXPDIR, key)) {
				if(COPY_SUCCESS != json_copy_int_array(&banner->expdir, &banner->nexpdir, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_EXPDIR);
					return retval;
				}
				break;
			}

			if (!strcmp(ORTB_API, key)) {
				if(COPY_SUCCESS != json_copy_int_array(&banner->api, &banner->napi, val)) {
					ORTB_ERROR("Failed to copy: %s", ORTB_API);
					return retval;
				}
				break;
			}

			ORTB_ERROR("Invalid key in Banner object: key: %s", key);
		}while(0);
	}

	retval = PARSE_SUCCESS;
	return retval;
}

int parseImpression(json_object* imps, BidRequest *bidRequest) {
	ORTB_LOG("In parseImpression() Parsing Impression Object");
	int retval = PARSE_FAILED;
	int idx = 0;
	int len = 0;
	bidRequest->impressions.impression=NULL;
	if (NULL == imps) {
		ORTB_ERROR("Impression is absent in bidrequest");
		return retval;
	}
	len = json_object_array_length(imps);
	if(len == 0) {
		ORTB_ERROR("Impression is absent in bidrequest");
		return retval;
	}

	int nelement = 0;
	for(idx = 0; idx < len; idx++) { // iterating over impressions
		json_object* imp = json_object_array_get_idx(imps, idx);
		if (NULL == imp) {
			ORTB_ERROR("Null Impression");
			return retval;
		}
		Impression impression;
		json_object_object_foreach(imp, key, val) {
		do{
			ORTB_LOG("Impression:Key:%s", key);
		
			if (NULL == val) {
				ORTB_LOG("NULL value found for key: %s", key);
				continue;
			}


			if (!strcmp(ORTB_ID, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression.id, val)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_ID);
						return retval;
				}
				break;
			}
		
			if (!strcmp(ORTB_BANNER, key)) {
				retval = parseBanner(val, &impression);
				if (PARSE_SUCCESS != retval) {
					ORTB_ERROR("Failed to parse:%s", ORTB_BANNER);
					return retval;
				}
				break;
			}
			
			if (!strcmp(ORTB_BIDFLOOR, key)){
				impression.bidfloor=json_object_get_double(val);
				break;
			}

			if (!strcmp(ORTB_INSTL,key)) {
				impression.instl=json_object_get_int(val);
				break;
			}
	
			if(!strcmp(ORTB_SECURE,key)){
				impression.secure=json_object_get_int(val);
				break;
			}

			if(!strcmp(ORTB_DISPLAYMANAGER, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression.displaymanager, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_DISPLAYMANAGER);
	  	                      	return retval;
                     		}
                             	break;	
			}
				
			if(!strcmp(ORTB_DISPLAYMANAGERVER, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression.displaymanagerver, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_DISPLAYMANAGERVER);
	  	                      	return retval;
                     		}
                             	break;	
			}
			if(!strcmp(ORTB_TAGID, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression.tagid, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_TAGID);
	  	                      	return retval;
                     		}
                             	break;	
			}
			
			if(!strcmp(ORTB_BIDFLOORCUR, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression.bidfloorcur, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_BIDFLOORCUR);
	  	                      	return retval;
                     		}
                             	break;	
			}
			
			if(!strcmp(ORTB_IFRAMEBUSTER, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&impression.iframebuster,&impression.niframebuster, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_IFRAMEBUSTER);
	  	                      	return retval;
                     		}
                             	break;	
			}
					
		  }while(0);	
		}	
			
		nelement += 1;
                bidRequest->impressions.nimpression = nelement;
                bidRequest->impressions.impression = (Impression *)realloc(bidRequest->impressions.impression, nelement);
                bidRequest->impressions.impression[nelement-1]=impression;
	}

	return PARSE_SUCCESS;
}
int parsePublisher(json_object* publisher, Site *site) {
	ORTB_LOG("parsing Publisher");
	int retval = PARSE_FAILED;
	if (NULL == publisher) {
		ORTB_ERROR("Null value for Publisher key");
		return retval;
	}
	site->publisher = (Publisher *)malloc(sizeof(Publisher));
	json_object_object_foreach(publisher, key, val) {
		ORTB_LOG("parsePublisher:key:%s", key);
		do {
			if (NULL == val) {
				ORTB_LOG("Null value found for key: %s", key);
				continue;
			}

			if (!strcmp(ORTB_ID, key)) {
				if(COPY_SUCCESS != json_copy_string(&site->publisher->id, val)) {
						ORTB_ERROR("failed to copy:%s", ORTB_ID);
						return retval;
				}

				break;
			}
		}while(0);
	}
	return PARSE_SUCCESS;
}
int parseSite(json_object* site, BidRequest *bidRequest) {
	ORTB_LOG("parsing site");
	int retval = PARSE_FAILED;
	if (NULL == site) {
		ORTB_ERROR("Null value for site key");
		return retval;
	}
	bidRequest->site = (Site *)malloc(sizeof(Site));
	json_object_object_foreach(site, key, val) {
		ORTB_LOG("parseSite:key:%s", key);
		do {
			if (NULL == val) {
				ORTB_LOG("null value found for key: %s", key);
				continue;
			}

			if (!strcmp(ORTB_ID, key)) {
				if( COPY_SUCCESS != json_copy_string(&bidRequest->site->id, val)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_ID);
						return retval;
				}

				break;
			}
			
			if (!strcmp(ORTB_PUBLISHER, key)) {
				if(PARSE_SUCCESS != parsePublisher(val,bidRequest->site)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_PUBLISHER);
						return retval;
				}

				break;
			}
			


		}while(0);
	}
		
	return PARSE_SUCCESS;
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
		
			if (!strcmp(ORTB_IMP, key)) {
				retval = parseImpression(val, bidRequest);
				if (PARSE_SUCCESS != retval) {
					ORTB_ERROR("Failed to parse:%s", ORTB_IMP);
					return retval;
				}
				break;
			}
	
			if (!strcmp(ORTB_SITE,key)) {
				retval=parseSite(val, bidRequest);
				if (PARSE_SUCCESS != retval) {
					ORTB_ERROR("Failed to parse:%s",ORTB_SITE);
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
