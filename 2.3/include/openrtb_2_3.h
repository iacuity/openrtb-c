#ifndef OPENRTB_2_3_H
#define OPENRTB_2_3_H

enum O_RTB_ERROR {
	PARSE_SUCCESS,
	PARSE_FAILED,
	NO_MEMORY,
	COPY_SUCCESS
};

#define ORTB_ID						"id"
#define ORTB_TEST 				"test"
#define ORTB_AT 					"at"
#define ORTB_TMAX 				"tmax"
#define ORTB_WSEAT 				"wseat"
#define ORTB_ALLIMPS 			"allimps"
#define ORTB_CUR 					"cur"
#define ORTB_BCAT 				"bcat"
#define ORTB_BADV 				"badv"

typedef struct {
	char* id;						// "id"
}Impression;

typedef struct {
	Impression impression;
	int nimpression;
}Impressions;


typedef struct {
	char* id;						// "id"
	int test;						// "test"
	int at;							// "at"
	int tmax;						// "tmax"
	char** wseat;				// "wseat"
	int nwseat;
	int allimps;				// "allimps"
	char** cur;         // "cur"
	int ncur;
<<<<<<< HEAD
	char** bcat;				// "bcat"
	int nbcat;
	char** badv;				// "badv"
	int nbadv;
=======
	//char** bcat;				// "bcat"
	//int nbcat;
	//char** badv;				// "badv"
	//int nbadv;
>>>>>>> 909c302952839584b334bc4297ab33dcdcabec1f
	Impressions impressions;
}BidRequest;

int parseRequest(const char* src, BidRequest *bidRequest);
void freeBidRequest(BidRequest *bidRequest);

#endif
