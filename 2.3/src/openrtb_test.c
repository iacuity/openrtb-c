#include <stdio.h>
#include <stdlib.h>
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
	\"site\": { \"id\": \"102855\", \
			\"publisher\": { \"id\": \"8953\" \
			} \
		}, \
	\"device\": { \
	\"dnt\": 0, \
	\"ua\": \"Mozilla/5.0 (iPhone; CPU iPhone OS 6_1 like Mac OS X) \
		AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9A334 Safari/7534.48.3\", \
	\"ip\": \"123.145.167.189\", \
	\"ifa\": \"AA000DFE74168477C70D291f574D344790E0BB11\", \
	\"carrier\": \"VERIZON\", \
	\"language\": \"en\", \
	\"make\": \"Apple\", \"model\": \"iPhone\", \
	\"os\": \"iOS\", \"osv\": \"6.1\", \
	\"js\": 1, \
	\"connectiontype\": 3, \
	\"devicetype\": 1, \
	\"geo\": { \
	\"lat\": 35.012345, \"lon\": -115.12345, \
	\"country\": \"USA\", \
	\"metro\": \"803\", \
	\"region\": \"CA\", \"city\": \"Los Angeles\", \"zip\": \"90049\" \
	} \
	}, \
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

	// Validate Impression Object
	assert(1 == bidRequest->impressions.nimpression);
	assert(!strcmp("1",  bidRequest->impressions.impression[0].id));
	//assert(bidRequest->impressions.impression[0].bidfloor == float(0.03));

	// Validate Banner Object
	assert(250 == bidRequest->impressions.impression[0].banner->h);
	assert(300 == bidRequest->impressions.impression[0].banner->w);
	assert(0 == bidRequest->impressions.impression[0].banner->pos);
	// Validate Site and Publisher
	assert(!strcmp("102855",  bidRequest->site->id));
	assert(!strcmp("8953",  bidRequest->site->publisher->id));
	//Validate Device Object
	assert(!strcmp("123.145.167.189",  bidRequest->device->ip));
	assert(!strcmp("AA000DFE74168477C70D291f574D344790E0BB11",  bidRequest->device->ifa));
	assert(!strcmp("VERIZON",  bidRequest->device->carrier));
	assert(!strcmp("en",  bidRequest->device->language));
	assert(!strcmp("Apple",  bidRequest->device->make));
	assert(!strcmp("iPhone",  bidRequest->device->model));
	assert(!strcmp("iOS",  bidRequest->device->os));
	assert(!strcmp("6.1",  bidRequest->device->osv));
	assert(1 == bidRequest->device->devicetype);
	assert(1 == bidRequest->device->js);
	assert(3 == bidRequest->device->connectiontype);
	assert(0 == bidRequest->device->dnt);
	return 0;
}

int main() {
	BidRequest *bidRequest = (BidRequest *) malloc(sizeof(BidRequest));
	int ret = parseRequest(SAMPLE_BID_REQ, bidRequest);
	
	if (ret != PARSE_SUCCESS) {
		fprintf(stderr, "Error: failed to parse json\n");
		return 1;
	}

	validateBidRequest(bidRequest);

	freeBidRequest(bidRequest);

	double price = 11.2045;
	BidResponse resp;
	resp.id = "bid-id";
	resp.cur = "USD";
	resp.seat.seat = "seatname";
	resp.seat.bid.id = "internal-bid-id";
	resp.seat.bid.impid = "internal-bid-id";
	resp.seat.bid.price = price;
	resp.seat.bid.adm = "<AD Markup>";
	resp.seat.bid.cid = "campaign-id";
	resp.seat.bid.crid = "creative-id";
	
	char buff[2000] = {0};
	createORTBBidResponse(buff, &resp);
	printf ("The json object created: %s \n", buff);

	return 0;
}
