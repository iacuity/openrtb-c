#include <stdio.h>
#include <assert.h>
#include "openrtb_2_3.h"

#define SAMPLE_BID_REQ "{ \
	\"id\": \"80ce30c53c16e6ede735f123ef6e32361bfc7b22\", \
	\"imp\": [ { \"id\": \"1\", \
		     \"bidfloor\": 0.03, \ 
		     \"banner\": { \"h\": 250, \
				   \"w\": 300, \ 
				   \"pos\": 0 \ 
                                 } \ 
                   } \ 
                 ], \
	\"at\": 1, \
	\"tmax\": 120, \
	\"wseat\": [\"seat-1\", \"seat-2\"], \
	\"allimps\": 1, \
	\"cur\": [\"USD\", \"INR\"], \
	\"bcat\": [\"bcat-1\", \"bcat-2\"], \
	\"badv\": [\"badv-1\", \"badv-2\"], \
	}" 

int validateBidRequest(BidRequest *bidRequest) {
	assert(!strcmp("80ce30c53c16e6ede735f123ef6e32361bfc7b22", bidRequest->id));
	assert(1 == bidRequest->at);
	assert(120 == bidRequest->tmax);
	
	assert(2 == bidRequest->nwseat);
	assert(!strcmp("seat-1",  bidRequest->wseat[0]));
	assert(!strcmp("seat-2",  bidRequest->wseat[1]));
	
	assert(1 == bidRequest->allimps);
	
	assert(2 == bidRequest->ncur);
	assert(!strcmp("USD",  bidRequest->cur[0]));
	assert(!strcmp("INR",  bidRequest->cur[1]));
	
	assert(2 == bidRequest->nbcat);
	assert(!strcmp("bcat-1",  bidRequest->bcat[0]));
	assert(!strcmp("bcat-2",  bidRequest->bcat[1]));
	
	assert(2 == bidRequest->nbadv);
	assert(!strcmp("badv-1",  bidRequest->badv[0]));
	assert(!strcmp("badv-2",  bidRequest->badv[1]));
	return 0;
}

int main() {
	BidRequest bidRequest;
	int ret = parseRequest(SAMPLE_BID_REQ, &bidRequest);
	
	if (ret != PARSE_SUCCESS) {
		fprintf(stderr, "Error: failed to parse json\n");
		return 1;
	}

	validateBidRequest(&bidRequest);

	freeBidRequest(&bidRequest);

	return 0;
}
