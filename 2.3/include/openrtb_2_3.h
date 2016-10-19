#ifndef OPENRTB_2_3_H
#define OPENRTB_2_3_H

enum O_RTB_ERROR {
	PARSE_SUCCESS,
	PARSE_FAILED,
	NO_MEMORY,
	COPY_SUCCESS
};

// REQUEST
#define ORTB_ID						"id"
#define ORTB_TEST 				"test"
#define ORTB_AT 					"at"
#define ORTB_TMAX 				"tmax"
#define ORTB_WSEAT 				"wseat"
#define ORTB_ALLIMPS 			"allimps"
#define ORTB_CUR 					"cur"
#define ORTB_BCAT 				"bcat"
#define ORTB_BADV 				"badv"

// IMPRESSION
#define ORTB_BANNER									"banner"
#define ORTB_VIDEO									"video"
#define ORTB_NATIVE									"native"
#define ORTB_DISPLAYMANAGER					"displaymanager"
#define ORTB_DISPLAYMANAGERVER			"displaymanagerver"
#define ORTB_INSTL									"instl"
#define ORTB_TAGID									"tagid"
#define ORTB_BIDFLOOR								"bidfloor"
#define ORTB_BIDFLOORCUR						"bidfloorcur"
#define ORTB_SECURE									"secure"
#define ORTB_IFRAMEBUSTER						"iframebuster"
#define	ORTB_PMP										"pmp"

// BANNER
#define ORTB_W											"w"
#define ORTB_H											"h"
#define ORTB_WMAX										"wmax"
#define ORTB_HMAX										"hmax"
#define ORTB_WMIN										"wmin"
#define ORTB_HMIN										"hmin"
#define ORTB_BTYPE									"btype"
#define ORTB_BATTR									"battr"
#define ORTB_POS										"pos"
#define ORTB_MIMES									"mimes"
#define ORTB_TOPFRAME								"topframe"
#define ORTB_EXPDIR									"expdir"
#define ORTB_API										"api"

// VIDEO
#define ORTB_MIMES									"mimes"
#define ORTB_MINDURATION						"minduration"
#define ORTB_MAXDURATION						"maxduration"
#define ORTB_PROTOCOL								"protocol"
#define ORTB_PROTOCOLS							"protocols"
#define ORTB_STARTDELAY							"startdelay"
#define ORTB_LINEARITY							"linearity"
#define ORTB_SEQUENCE								"sequence"
#define ORTB_MAXEXTENDED						"maxextended"
#define ORTB_MINBITRATE							"minbitrate"
#define ORTB_MAXBITRATE							"maxbitrate"
#define ORTB_BOXINGALLOWED					"boxingallowed"
#define ORTB_PLAYBACKMETHOD					"playbackmethod"
#define ORTB_DELIVERY								"delivery"
#define ORTB_COMPANIONAD						"companionad"
#define ORTB_COMPANIONTYPE 					"companiontype"

// NATIVE
#define ORTB_REQUEST								"request"

// SITE
#define ORTB_NAME										"name"
#define ORTB_DOMAIN									"domain"
#define ORTB_CAT										"cat"
#define ORTB_SECTIONCAT							"sectioncat"
#define ORTB_PAGECAT								"pagecat"
#define ORTB_REF										"ref"
#define ORTB_SEARCH									"search"
#define ORTB_MOBILE									"mobile"
#define ORTB_PRIVACYPOLICY					"privacypolicy"
#define ORTB_KEYWORDS								"keywords"

// APP
#define ORTB_BUNDLE									"bundle"
#define ORTB_STOREURL								"storeurl"
#define ORTB_VER										"ver"
#define ORTB_PAID										"paid"

// DEVICE
#define ORTB_UA											"ua"
#define ORTB_DNT										"dnt"
#define ORTB_LMT										"lmt"
#define ORTB_IP											"ip"
#define ORTB_IPV6										"ipv6"
#define ORTB_DEVICETYPE							"devicetype"
#define ORTB_MAKE										"make"
#define ORTB_MODEL									"model"
#define ORTB_OS											"os"
#define ORTB_OSV										"osv"
#define ORTB_HWV										"hwv"
#define ORTB_PPI										"ppi"
#define ORTB_PXRATIO								"pxratio"
#define ORTB_JS											"js"
#define ORTB_FLASHVER								"flashver"
#define ORTB_LANGUAGE								"language"
#define ORTB_CARRIER								"carrier"
#define ORTB_CONNECTIONTYPE					"connectiontype"
#define ORTB_IFS										"ifa"
#define ORTB_DIDSHA1								"didsha1"
#define ORTB_DIDMD5									"didmd5"
#define ORTB_DPIDSHA1								"dpidsha1"
#define ORTB_DPIDMD5								"dpidmd5"
#define ORTB_MACSHA1								"macsha1"
#define ORTB_MACMD5									"macmd5"

// USER
#define ORTB_BUYERID								"buyerid"
#define ORTB_YOB										"yob"
#define ORTB_GENDER									"gender"
#define ORTB_CUSTOMDATA							"customdata"

// REGS
#define ORTB_COPPA									"coppa"

typedef struct {
	int coppa;							// "coppa"
}Regs;

typedef struct {
	char* id;								// "id"
	char* buyerid;					// "buyerid"
	int yob;								// "yob"
	char* gender;						// "gender"
	char* keywords;					// "keywords"
	char* customdata;				// "customdata"
}User;

typedef struct {
	char* ua;								// "ua"
	int dnt;								// "dnt"
	int lmt;								// "lmt"
	char* ip;								// "ip"
	char* ipv6;							// "ipv6"
	int devicetype;					// "devicetype"
	char* make;							// "make"
	char* model;						// "model"
	char* os;								// "os"
	char* osv;							// "osv"
	char* hwv;							// "hwv"
	int h;									// "h"
	int w;									// "w"
	int ppi;								// "ppi"
	float pxratio;					// "pxratio"
	int js;									// "js"
	char* flashver;					// "flashver"
	char* language;					// "language"
	char* carrier;					// "carrier"
	int connectiontype;			// "connectiontype"
	char* ifa;							// "ifa"
	char* didsha1;					// "didsha1"
	char* didmd5;						// "didmd5"
	char* dpidsha1;					// "dpidsha1"
	char* dpidmd5;					// "dpidmd5"
	char* macsha1;					// "macsha1"
	char* macmd5;						// "macmd5"
}Device;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	char* bundle;						// "bundle"
	char* domain;						// "domain"
	char* storeurl;					// "storeurl"
	char** cat;							// "cat"
	char** sectioncat;			// "sectioncat"
	char** pagecat;					// "pagecat"
	char* ver;							// "ver"
	int privacypolicy;			// "privacypolicy"
	int paid;								// "paid"
	char* keywords;					// "keywords"
}App;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	char* domain;						// "domain"
	char** cat;							// "cat"
	char** sectioncat;			// "sectioncat"
	char** pagecat;					// "pagecat"
	char* ref;							// "ref"
	char* search;						// "search"
	int mobile;							// "mobile"
	int privacypolicy;			// "privacypolicy"
	char* keywords;					// "keywords"
}Site;

typedef struct {
	char* request;					// "request"
	char* ver;							// "ver"
	char* api;							// "api"
	int* battr;							// "battr"
}Native;

typedef struct {
	char** mimes;						// "mimes"
	int minduration;				// "minduration"
	int maxduration;				// "maxduration"
	int protocol;						// "protocol" // DEPRECATED -> suggested protocols
	int* protocols;					// "protocols"
	int w;									// "w"
	int h;									// "h"
	int startdelay;					// "startdelay"
	int linearity;					// "linearity"
	int sequence;						// "sequence"
	int *battr;							// "battr"
	int maxextended;				// "maxextended"
	int minbitrate;					// "minbitrate"
	int maxbitrate;					// "maxbitrate"
	int boxingallowed;			// "boxingallowed"
	int* playbackmethod;		// "playbackmethod"
	int* delivery;					// "delivery"
	int pos;								// "pos"
	int* companionad;				// "companionad"
	int* api;								// "api"
	int* companiontype;			// "companiontype"
}Video;

typedef struct {
	int w;									// "w"
	int h;									// "h"
	int wmax;								// "wmax"
	int hmax;								// "hmax"
	int wmin;								// "wmin"
	int hmin;								// "hmin"
	char* id;								// "id"
	int* btype;							// "btype"
	int* battr;							// "battr"
	int pos;								// "pos"
	char** mimes;						// "mimes"
	int topframe;						// "topframe"
	int* expdir;						// "expdir"
	int* api;								// "api"
}Banner;

typedef struct {
	char* id;								// "id"
	Banner *banner;
	Video *video;
	Native *native;
	char* displaymanager;		// "displaymanager"
	char* displaymanagerver;// "displaymanagerver"
	int instl;							// "instl"
	char* tagid;						// "tagid"
	float bidfloor;					// "bidfloor"
	char* bidfloorcur;			// "bidfloorcur"
	int secure;							// "secure"
	char** iframebuster;		// "iframebuster"
	int niframebuster;
}Impression;

typedef struct {
	Impression *impression;
	int nimpression;
}Impressions;


typedef struct {
	char* id;						// "id"
	Impressions impressions;
	Site *site;
	App *app;
	Device *device;
	User *user;
	int test;						// "test"
	int at;							// "at"
	int tmax;						// "tmax"
	char** wseat;				// "wseat"
	int nwseat;
	int allimps;				// "allimps"
	char** cur;         // "cur"
	int ncur;
	char** bcat;				// "bcat"
	int nbcat;
	char** badv;				// "badv"
	int nbadv;
	Regs *regs;
}BidRequest;

int parseRequest(const char* src, BidRequest *bidRequest);
void freeBidRequest(BidRequest *bidRequest);

#endif
