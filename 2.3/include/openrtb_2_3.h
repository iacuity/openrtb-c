#ifndef OPENRTB_2_3_H
#define OPENRTB_2_3_H

enum O_RTB_ERROR {
	PARSE_SUCCESS,
	PARSE_FAILED,
	NO_MEMORY_AVAILABLE,
	COPY_SUCCESS
};

// REQUEST
#define ORTB_ID                     "id"
#define ORTB_IMP                    "imp"
#define ORTB_TEST                   "test"
#define ORTB_AT                     "at"
#define ORTB_TMAX                   "tmax"
#define ORTB_WSEAT                  "wseat"
#define ORTB_ALLIMPS                "allimps"
#define ORTB_CUR                    "cur"
#define ORTB_BCAT                   "bcat"
#define ORTB_BADV                   "badv"

// IMPRESSION
#define ORTB_BANNER                 "banner"
#define ORTB_VIDEO                  "video"
#define ORTB_NATIVE                 "native"
#define ORTB_DISPLAYMANAGER         "displaymanager"
#define ORTB_DISPLAYMANAGERVER      "displaymanagerver"
#define ORTB_INSTL                  "instl"
#define ORTB_TAGID                  "tagid"
#define ORTB_BIDFLOOR               "bidfloor"
#define ORTB_BIDFLOORCUR            "bidfloorcur"
#define ORTB_SECURE                 "secure"
#define ORTB_IFRAMEBUSTER           "iframebuster"
#define ORTB_PMP                    "pmp"

// BANNER
#define ORTB_W                      "w"
#define ORTB_H                      "h"
#define ORTB_WMAX                   "wmax"
#define ORTB_HMAX                   "hmax"
#define ORTB_WMIN                   "wmin"
#define ORTB_HMIN                   "hmin"
#define ORTB_BTYPE                  "btype"
#define ORTB_BATTR                  "battr"
#define ORTB_POS                    "pos"
#define ORTB_MIMES                  "mimes"
#define ORTB_TOPFRAME               "topframe"
#define ORTB_EXPDIR                 "expdir"
#define ORTB_API                    "api"

// VIDEO
#define ORTB_MINDURATION            "minduration"
#define ORTB_MAXDURATION            "maxduration"
#define ORTB_PROTOCOL               "protocol"
#define ORTB_PROTOCOLS              "protocols"
#define ORTB_STARTDELAY             "startdelay"
#define ORTB_LINEARITY              "linearity"
#define ORTB_SEQUENCE               "sequence"
#define ORTB_MAXEXTENDED            "maxextended"
#define ORTB_MINBITRATE             "minbitrate"
#define ORTB_MAXBITRATE             "maxbitrate"
#define ORTB_BOXINGALLOWED          "boxingallowed"
#define ORTB_PLAYBACKMETHOD         "playbackmethod"
#define ORTB_DELIVERY               "delivery"
#define ORTB_COMPANIONAD            "companionad"
#define ORTB_COMPANIONTYPE          "companiontype"

// NATIVE
#define ORTB_REQUEST                "request"

// PMP
#define ORTB_PRIVATEAUCTION         "private_auction"
#define ORTB_DEALS                  "deals"

// DEAL
#define ORTB_BIDFLOOR               "bidfloor"
#define ORTB_BIDFLOORCUR            "bidfloorcur"
#define ORTB_WADOMAIN               "wadomain"

// SITE
#define ORTB_GEO                    "geo"
#define ORTB_NAME                   "name"
#define ORTB_DOMAIN                 "domain"
#define ORTB_CAT                    "cat"
#define ORTB_SECTIONCAT             "sectioncat"
#define ORTB_PAGECAT                "pagecat"
#define ORTB_REF                    "ref"
#define ORTB_SEARCH                 "search"
#define ORTB_MOBILE                 "mobile"
#define ORTB_PRIVACYPOLICY          "privacypolicy"
#define ORTB_KEYWORDS               "keywords"
#define ORTB_PUBLISHER              "publisher"
#define ORTB_CONTENT                "content"

// APP
#define ORTB_BUNDLE                 "bundle"
#define ORTB_STOREURL               "storeurl"
#define ORTB_VER                    "ver"
#define ORTB_PAID                   "paid"

// CONTENT
#define ORTB_EPISODE                "episode"
#define ORTB_TITLE                  "title"
#define ORTB_SERIES                 "series"
#define ORTB_SEASON                 "season"
#define ORTB_URL                    "url"
#define ORTB_VDEOQUALITY            "videoquality"
#define ORTB_CONTEXT                "context"
#define ORTB_CONTENTRATING          "contentrating"
#define ORTB_USERRATIING            "userrating"
#define ORTB_QAFMEDIARATING         "qagmediarating"
#define ORTB_LIVESTREAM             "livestream"
#define ORTB_SOURCERELATIONSHIP     "sourcerelationship"
#define ORTB_LEN                    "len"
#define ORTB_LANGUAGE               "language"
#define ORTB_EMBEDDABLE             "embeddable"

// DEVICE
#define ORTB_UA                     "ua"
#define ORTB_DNT                    "dnt"
#define ORTB_LMT                    "lmt"
#define ORTB_IP                     "ip"
#define ORTB_IPV6                   "ipv6"
#define ORTB_DEVICETYPE             "devicetype"
#define ORTB_MAKE                   "make"
#define ORTB_MODEL                  "model"
#define ORTB_OS                     "os"
#define ORTB_OSV                    "osv"
#define ORTB_HWV                    "hwv"
#define ORTB_PPI                    "ppi"
#define ORTB_PXRATIO                "pxratio"
#define ORTB_JS                     "js"
#define ORTB_FLASHVER               "flashver"
#define ORTB_CARRIER                "carrier"
#define ORTB_CONNECTIONTYPE         "connectiontype"
#define ORTB_IFS                    "ifa"
#define ORTB_DIDSHA1                "didsha1"
#define ORTB_DIDMD5                 "didmd5"
#define ORTB_DPIDSHA1               "dpidsha1"
#define ORTB_DPIDMD5                "dpidmd5"
#define ORTB_MACSHA1                "macsha1"
#define ORTB_MACMD5                 "macmd5"

// GEO
#define ORTB_LAT                    "lat"
#define ORTB_LON                    "lon"
#define ORTB_TYPE                   "type"
#define ORTB_COUNTRY                "country"
#define ORTB_REGION                 "region"
#define ORTB_REGIONFIPS104          "regionfips104"
#define ORTB_METRO                  "metro"
#define ORTB_CITY                   "city"
#define ORTB_ZIP                    "zip"
#define ORTB_UTCOFFSET              "utcoffset"

// SEGMENT
#define ORTB_SEGMENT                "segment"
#define ORTB_VALUE                  "value"

// USER
#define ORTB_BUYERID                "buyerid"
#define ORTB_YOB                    "yob"
#define ORTB_GENDER                 "gender"
#define ORTB_CUSTOMDATA             "customdata"

// REGS
#define ORTB_COPPA                  "coppa"

typedef struct {
	int coppa;							// "coppa"
}Regs;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	char* value;						// "value"
}Segment;

typedef struct {
	Segment *segment;
	int nsegment;
}Segments;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	Segments* segment;			// "segment"
}Data;

typedef struct {
	Data *data;
	int ndata;
}Datas;

typedef struct {
	float lat;							// "lat"
	float lon;							// "lon"
	int type;								// "type"
	char* country;					// "country"
	char* region;						// "region"
	char* regionfips104;		// "regionfips104"
	char* metro;						// "metro"
	char* city;							// "city"
	char* zip;							// "zip"
	int utcoffset;					// "utcoffset"
}Geo;

typedef struct {
	char* id;								// "id"
	char* buyerid;					// "buyerid"
	int yob;								// "yob"
	char* gender;						// "gender"
	char* keywords;					// "keywords"
	char* customdata;				// "customdata"
	Geo *geo;								// "geo"
	Datas* data;						// "data"
}User;

typedef struct {
	char* ua;								// "ua"
	//Geo *geo;								// "geo"
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

typedef struct{
	char* id;								// "id"
	int episode;						// "episode"
	char* title;						// "title"
	char* series;						// "series"
	char* season;						// "season"
	char* url;							// "url"
	char** cat;							// "cat"
	int videoquality;				// "videoquality"
	int context;						// "context"
	char* contentrating;		// "contentrating"
	char* userrating;				// "userrating"
	int qagmediarating;			// "qagmediarating"
	char* keywords;					// "keywords"
	int livestream;					// "livestream"
	int sourcerelationship;	// "sourcerelationship"
	int len;								// "len"
	char* language;					// "language"
	int embeddable;					// "embeddable"
}Content;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	char** cat;							// "cat"
	char* domain;						// "domain"
}Publisher;

typedef struct {
	char* id;								// "id"
	char* name;							// "name"
	char** cat;							// "cat"
	char* domain;						// "domain"
}Producer;

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
	Publisher* publisher;		// "publisher"
	Content* content;				// "content"
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
	Publisher* publisher;		// "publisher"
	Content* content;				// "content"
	char* keywords;					// "keywords"
}Site;

typedef struct {
	char* id;								// "id"
	float bidfloor;					// "bidfloor"
	char* bidfloorcur;			// "bidfloorcur"
	int at;									// "at"
	char** wseat;						// "wseat"
	int nwseat;
	char** wadomain;				// "wadomain"
	int nwadomain;
}Deal;

typedef struct {
	Deal *deal;
	int ndeal;
}Deals;

typedef struct {
	int private_auction;		// "private_auction"
	Deals *deals;						// "deals"
}Pmp;

typedef struct {
	char* request;					// "request"
	char* ver;							// "ver"
	char* api;							// "api"
	int* battr;							// "battr"
}Native;

typedef struct {
	int w;									// "w"
	int h;									// "h"
	int wmax;								// "wmax"
	int hmax;								// "hmax"
	int wmin;								// "wmin"
	int hmin;								// "hmin"
	char* id;								// "id"
	int* btype;							// "btype"
	int nbtype;
	int* battr;							// "battr"
	int nbattr;
	int pos;								// "pos"
	char** mimes;						// "mimes"
	int nmimes;
	int topframe;						// "topframe"
	int* expdir;						// "expdir"
	int nexpdir;
	int* api;								// "api"
	int napi;
}Banner;

typedef struct {
	Banner *banner;
	int nbanner;
}CompanionAd;

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
	CompanionAd* companionad;				// "companionad"
	int* api;								// "api"
	int* companiontype;			// "companiontype"
}Video;

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
	Pmp *pmp;
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
