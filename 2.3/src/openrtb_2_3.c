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

/*void freeBidRequest(BidRequest *bidRequest) {
	do{
		if (NULL == bidRequest)
			break;

		FREE_AND_RESET(bidRequest->id);
		FREE_AND_RESET_LIST(bidRequest->nwseat, bidRequest->wseat);	
		FREE_AND_RESET_LIST(bidRequest->ncur, bidRequest->cur);	

		FREE_AND_RESET_LIST(bidRequest->nbcat, bidRequest->bcat);	
		FREE_AND_RESET_LIST(bidRequest->nbadv, bidRequest->badv);	
	}while(0);
}*/

void freeStringArray(char **str, int num){
	int i;
	for(i=0;i<num;i++)
		free(str[i]);
}

void freePublisherObject(Publisher *pub){
	if(pub == NULL)
		return;
	if(pub->id != NULL){
		free(pub->id);
		pub->id = NULL;
	}
	if(pub->name != NULL){
		free(pub->name);
		pub->name = NULL;
	}
	if(pub->cat != NULL){
		free(pub->cat);
		pub->cat = NULL;
	}
	if(pub->domain != NULL){
		free(pub->domain);
		pub->domain = NULL;
	}
	free(pub);
}

void freeSiteObject(Site *site){
	if(site == NULL)
		return;
	if(site->id != NULL){
		free(site->id);
		site->id = NULL;
	}
	if(site->name != NULL){
		free(site->name);
		site->name = NULL;
	}
	if(site->domain != NULL){
		free(site->domain);
		site->domain = NULL;
	}
	if(site->cat != NULL){
		free(site->cat);
		site->cat = NULL;
	}
	if(site->sectioncat != NULL){
		free(site->sectioncat);
		site->sectioncat = NULL;
	}
	if(site->pagecat != NULL){
		free(site->pagecat);
		site->pagecat = NULL;
	}
	if(site->ref != NULL){
		free(site->ref);
		site->ref = NULL;
	}
	if(site->search != NULL){
		free(site->search);
		site->search = NULL;
	}
	if(site->publisher != NULL){
		freePublisherObject(site->publisher);
		site->publisher = NULL;
	}
	if(site->content != NULL){
		//freeContentObject();
		site->content = NULL;
	}
	if(site->keywords != NULL){
		free(site->keywords);
		site->keywords = NULL;
	}
	free(site);
}

void freeBannerObject(Banner *banner){
	if(banner == NULL)
		return;
	if(banner->id != NULL){
		free(banner->id);
		banner->id = NULL;
	}
	if(banner->btype != NULL){
		free(banner->btype);
		banner->btype = NULL;
		banner->nbtype = 0;
	}
	if(banner->battr != NULL){
		free(banner->battr);
		banner->battr = NULL;
		banner->nbattr = 0;
	}
	if(banner->mimes != NULL){
		freeStringArray(banner->mimes, banner->nmimes);
		free(banner->mimes);
		banner->mimes = NULL;
		banner->nmimes = 0;
	}
	if(banner->expdir = NULL){
		free(banner->expdir);
		banner->expdir = NULL;
		banner->nexpdir = 0;
	}
	if(banner->api != NULL){
		free(banner->api);
		banner->api = NULL;
		banner->napi = 0;
	}
	free(banner);
}

void freeImpressionObject(Impression *imp){
	if(imp == NULL)
		return;
	if(imp->id != NULL){
		free(imp->id);
		imp->id = NULL;
	}
	if(imp->banner != NULL){
		freeBannerObject(imp->banner);
		imp->banner = NULL;
	}
	if(imp->video != NULL){
		//freeVideoObject(imp->video);
		imp->video = NULL;
	}
	if(imp->native != NULL){
		//freeNativeObject(imp->native);
		imp->native = NULL;
	}
	if(imp->displaymanager != NULL){
		free(imp->displaymanager);
		imp->displaymanager = NULL;
	}
	if(imp->displaymanagerver != NULL){
		free(imp->displaymanagerver);
		imp->displaymanagerver = NULL;
	}
	if(imp->tagid != NULL){
		free(imp->tagid );
		imp->tagid = NULL;
	}
	if(imp->bidfloorcur != NULL){
		free(imp->bidfloorcur);
		imp->bidfloorcur = NULL;
	}
	if(imp->iframebuster != NULL){
		freeStringArray(imp->iframebuster, imp->niframebuster);
		free(imp->iframebuster);
		imp->iframebuster = NULL;
		imp->niframebuster = 0;
	}
	if(imp->pmp != NULL){
		//freePmpObject(imp->pmp);
		imp->pmp = NULL;
	}
	free(imp);
}

void freeBidRequest(BidRequest *bidRequest){
	if(bidRequest == NULL)
		return;
	int i;
	if(bidRequest->id != NULL){
		free(bidRequest->id);
		bidRequest->id = NULL;
	}
	if(bidRequest->site != NULL){
		freeSiteObject(bidRequest->site);
		bidRequest->site = NULL;
	}
	if(bidRequest->app != NULL){
		//freeAppObject(bidRequest->app);
		bidRequest->app = NULL;
	}
	if(bidRequest->device != NULL){
		//freeDeviceObject(bidRequest->device);
		bidRequest->device = NULL;
	}
	if(bidRequest->user != NULL){
		//freeUserObject(bidRequest->user);
		bidRequest->user = NULL;
	}
	if(bidRequest->wseat != NULL){
		freeStringArray(bidRequest->wseat, bidRequest->nwseat);
		free(bidRequest->wseat);
		bidRequest->wseat = NULL;
		bidRequest->nwseat = 0;
	}
	if(bidRequest->cur != NULL){
		freeStringArray(bidRequest->cur, bidRequest->ncur);
		free(bidRequest->cur);
		bidRequest->cur = NULL;
		bidRequest->ncur = 0;
	}
	if(bidRequest->bcat != NULL){
		freeStringArray(bidRequest->bcat, bidRequest->nbcat);
		free(bidRequest->bcat);
		bidRequest->bcat = NULL;
		bidRequest->nbcat = 0;
	}
	if(bidRequest->badv != NULL){
		freeStringArray(bidRequest->badv, bidRequest->nbadv);
		free(bidRequest->badv);
		bidRequest->badv = NULL;
		bidRequest->nbadv = 0;
	}
	if(bidRequest->regs != NULL){
		//freeRegsObject(bidRequest->regs);
		bidRequest->regs = NULL;
	}
	if(bidRequest->impressions.impression != NULL){
		for(i=0; i< bidRequest->impressions.nimpression; i++){
			freeImpressionObject(bidRequest->impressions.impression+i);
		}
		bidRequest->impressions.nimpression = 0;
		bidRequest->impressions.impression = NULL;
	}
	free(bidRequest);
}

int initBidRequestObject(BidRequest *bidRequest){
	if(bidRequest == NULL)
		return -1;
	bidRequest->id = NULL;
	bidRequest->site = NULL;
	bidRequest->app = NULL;
	bidRequest->device = NULL;
	bidRequest->user = NULL;
	bidRequest->test = 0;
	bidRequest->at = 2;
	bidRequest->tmax = 0;
	bidRequest->wseat = NULL;
	bidRequest->nwseat = 0;
	bidRequest->allimps = 0;
	bidRequest->cur = NULL;
	bidRequest->ncur = 0;
	bidRequest->bcat = NULL;
	bidRequest->nbcat = 0;
	bidRequest->badv = NULL;
	bidRequest->nbadv = 0;
	bidRequest->regs = NULL;
	bidRequest->impressions.nimpression = 0;
	bidRequest->impressions.impression = NULL;
	return 0;
}

int initImpressionObject(Impression *imp){
	if(imp == NULL)
		return -1;
	imp->id = NULL;	
	imp->banner = NULL;
	imp->video = NULL;
	imp->native = NULL;
	imp->displaymanager = NULL;
	imp->displaymanagerver = NULL;
	imp->instl = 0;	
	imp->tagid = NULL;
	imp->bidfloor = 0;
	imp->bidfloorcur = NULL;
	imp->secure = 0;
	imp->iframebuster = NULL;
	imp->niframebuster = 0;
	imp->pmp = NULL;
	return 0;
}

int initBannerObject(Banner *banner){
	if(banner == NULL)
		return -1;
	banner->w = 0;
	banner->h = 0;
	banner->wmax = 0;
	banner->hmax = 0;
	banner->wmin = 0;
	banner->hmin = 0;
	banner->id = NULL;
	banner->btype = NULL;
	banner->nbtype = 0;
	banner->battr = NULL;
	banner->nbattr = 0;
	banner->pos = 0;
	banner->mimes = NULL;
	banner->nmimes = 0;
	banner->topframe = 0;
	banner->expdir = NULL;
	banner->nexpdir = 0;
	banner->api = NULL;
	banner->napi = 0;
	return 0;
}

int initSiteObject(Site *site){
	site->id = NULL;
	site->name = NULL;
	site->domain = NULL;
	site->cat = NULL;
	site->sectioncat = NULL;
	site->pagecat = NULL;
	site->ref = NULL;
	site->search = NULL;
	site->mobile = 0;
	site->privacypolicy = 0;
	site->publisher = NULL;
	site->content = NULL;
	site->keywords = NULL;
}

int initPublisherObject(Publisher *pub){
	pub->id = NULL;
	pub->name = NULL;
	pub->cat = NULL;
	pub->domain = NULL;
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
	initBannerObject(banner);
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
		nelement += 1;
                bidRequest->impressions.nimpression = nelement;
                bidRequest->impressions.impression = (Impression *)realloc(bidRequest->impressions.impression, sizeof(Impression) * nelement);
		Impression *impression = bidRequest->impressions.impression + (nelement - 1);
		initImpressionObject(impression);
		json_object_object_foreach(imp, key, val) {
		do{
			ORTB_LOG("Impression:Key:%s", key);
		
			if (NULL == val) {
				ORTB_LOG("NULL value found for key: %s", key);
				continue;
			}


			if (!strcmp(ORTB_ID, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression->id, val)) {
						ORTB_ERROR("Failed to copy:%s", ORTB_ID);
						return retval;
				}
				break;
			}
		
			if (!strcmp(ORTB_BANNER, key)) {
				retval = parseBanner(val, impression);
				if (PARSE_SUCCESS != retval) {
					ORTB_ERROR("Failed to parse:%s", ORTB_BANNER);
					return retval;
				}
				break;
			}
			
			if (!strcmp(ORTB_BIDFLOOR, key)){
				impression->bidfloor=json_object_get_double(val);
				break;
			}

			if (!strcmp(ORTB_INSTL,key)) {
				impression->instl=json_object_get_int(val);
				break;
			}
	
			if(!strcmp(ORTB_SECURE,key)){
				impression->secure=json_object_get_int(val);
				break;
			}

			if(!strcmp(ORTB_DISPLAYMANAGER, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression->displaymanager, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_DISPLAYMANAGER);
	  	                      	return retval;
                     		}
                             	break;	
			}
				
			if(!strcmp(ORTB_DISPLAYMANAGERVER, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression->displaymanagerver, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_DISPLAYMANAGERVER);
	  	                      	return retval;
                     		}
                             	break;	
			}
			if(!strcmp(ORTB_TAGID, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression->tagid, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_TAGID);
	  	                      	return retval;
                     		}
                             	break;	
			}
			
			if(!strcmp(ORTB_BIDFLOORCUR, key)) {
				if(COPY_SUCCESS != json_copy_string(&impression->bidfloorcur, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_BIDFLOORCUR);
	  	                      	return retval;
                     		}
                             	break;	
			}
			
			if(!strcmp(ORTB_IFRAMEBUSTER, key)) {
				if(COPY_SUCCESS != json_copy_string_array(&impression->iframebuster,&impression->niframebuster, val)) {
                	       		ORTB_ERROR("Failed to copy:%s", ORTB_IFRAMEBUSTER);
	  	                      	return retval;
                     		}
                             	break;	
			}
					
		  }while(0);	
		}	
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
	initPublisherObject(site->publisher);
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
	initSiteObject(bidRequest->site);
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

	initBidRequestObject(bidRequest);
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
	json_object* root = NULL;
	root = json_tokener_parse(src);
	int retval = PARSE_FAILED; 
	if (NULL == root) {
		ORTB_ERROR("Failed to parse bidrequest JSON");
		return retval;
	}
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

int createORTBBidResponse(char *buff, BidResponse *resp) {
	/*Creating a json object*/
	json_object *jresp = json_object_new_object();
	
	// start-seat create seatbid array
	json_object *jseatbids = json_object_new_array();
	
	// start-bid create bid array
	json_object *jbids = json_object_new_array();

	json_object *jbidobj = json_object_new_object();
	json_object *jbidid = json_object_new_string(resp->seat.bid.id);
	json_object_object_add (jbidobj, ORTB_RESP_ID, jbidid);
	json_object *jbidimpid = json_object_new_string(resp->seat.bid.impid);
	json_object_object_add (jbidobj, ORTB_RESP_IMPID, jbidimpid);

	char tempbuffprice[20];
	sprintf(tempbuffprice, "%.6f", resp->seat.bid.price);

	json_object *jbidprice = json_object_new_double_s(resp->seat.bid.price, tempbuffprice);
	json_object_object_add (jbidobj, ORTB_RESP_PRICE, jbidprice);

	json_object *jbidcid = json_object_new_string(resp->seat.bid.cid);
	json_object_object_add (jbidobj, ORTB_RESP_CID, jbidcid);
	json_object *jbidcrid = json_object_new_string(resp->seat.bid.crid);
	json_object_object_add (jbidobj, ORTB_RESP_CRID, jbidcrid);
	json_object_array_add(jbids, jbidobj);
	// end-bid 

	json_object *jseatobj = json_object_new_object();
	json_object_object_add (jseatobj, ORTB_RESP_BID, jbids);
	json_object *jseat = json_object_new_string(resp->seat.seat);
	json_object_object_add (jseatobj, ORTB_RESP_SEAT, jseat);
	json_object_array_add(jseatbids, jseatobj);
	// end-seat

	json_object *jbid = json_object_new_string(resp->id);
	json_object_object_add (jresp, ORTB_RESP_ID, jbid);
	
	json_object *jbcur = json_object_new_string(resp->cur);
	json_object_object_add (jresp, ORTB_RESP_CUR, jbcur);
	
	json_object_object_add (jresp, ORTB_RESP_SEAT_BID, jseatbids);

	/*Now printing the json object*/
	//const char* tempbuff = json_object_to_json_string(jresp);
	const char* tempbuff = json_object_to_json_string_ext(jresp, JSON_C_TO_STRING_PLAIN);
	strcpy(buff, tempbuff);

	json_object_put(jresp);
	
	return 0;
}


