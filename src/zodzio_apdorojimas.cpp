//
// Created by User on 2025-05-17.
//

#include "zodzio_apdorojimas.h"

#include <regex>

#include "rbtreemap.h"


void eilutes_apdorojimas(std::wstringstream& eilute) {

    const std::set<wchar_t> punctuation_marks = {
        L'.', L',', L';', L':', L'!', L'?', L'-', L'(', L')', L'[', L']', L'{', L'}', L'\'', L'"', L'/', L'\\', L'|', L'@', L'#', L'$', L'%', L'^', L'&', L'*', L'_', L'+', L'=', L'<', L'>', L'`', L'~',
        L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
        L'—', L'–', L'−', L'‐', L'‒', L'―'
    };
    // VIS DAR – NEVEIKIA DEL ENCODING URGHZTHIZWD! As myliu programavima ir problemu sprendima !

    wchar_t eilutes_char{};
    std::wstring result;
    while (eilute.get(eilutes_char)) {
        if (!punctuation_marks.contains(eilutes_char)) {
            result += towlower(eilutes_char);
        }
    }

    eilute.clear();
    eilute.str(result);
}

/*//Cia su regexu parase mostly chatukas, nes busiu honest as regexo normaliai nepernesu
void link_apdorojimas(std::vector<std::wstring>& links, std::wstringstream& eilute) {

    std::wregex url_regex(LR"(\b((https?:\/\/)?([a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,}(:\d+)?(\/\S*)?)\b)");

    std::wstring text = eilute.str();

    // Find all matches using wide character versions
    std::wsmatch matches;
    std::wstring::const_iterator searchStart(text.cbegin());

    while (std::regex_search(searchStart, text.cend(), matches, url_regex)) {
        // No conversion needed, already working with wstring
        std::wstring link = matches[1].str();
        links.push_back(link);

        // Move the search position forward
        searchStart = matches.suffix().first;
    }
}*/

void link_apdorojimas(std::vector<std::wstring>& links, std:: wstringstream& eilute) {
    // cia gal durnas metodas, bet aj galvoju tsg patikrint ar dalykas baigiasi su kazkokiu TLD, pvz. vu.lt baigiasi su .lt. Durnas sprendimas bet aj.
    // Alternatyva butu turbut ieskot kur keli zodziai yra.atskirti.tik.tasku, bet ajj kzn
    // su regexu butu sunku visus linkus aptikt

    std::set<std::wstring> tlds = {L"AAA", L"AARP", L"ABB", L"ABBOTT", L"ABBVIE", L"ABC", L"ABLE", L"ABOGADO", L"ABUDHABI", L"AC", L"ACADEMY", L"ACCENTURE", L"ACCOUNTANT", L"ACCOUNTANTS", L"ACO", L"ACTOR", L"AD", L"ADS", L"ADULT", L"AE", L"AEG", L"AERO", L"AETNA", L"AF", L"AFL", L"AFRICA", L"AG", L"AGAKHAN", L"AGENCY", L"AI", L"AIG", L"AIRBUS", L"AIRFORCE", L"AIRTEL", L"AKDN", L"AL", L"ALIBABA", L"ALIPAY", L"ALLFINANZ", L"ALLSTATE", L"ALLY", L"ALSACE", L"ALSTOM", L"AM", L"AMAZON", L"AMERICANEXPRESS", L"AMERICANFAMILY", L"AMEX", L"AMFAM", L"AMICA", L"AMSTERDAM", L"ANALYTICS", L"ANDROID", L"ANQUAN", L"ANZ", L"AO", L"AOL", L"APARTMENTS", L"APP", L"APPLE", L"AQ", L"AQUARELLE", L"AR", L"ARAB", L"ARAMCO", L"ARCHI", L"ARMY", L"ARPA", L"ART", L"ARTE", L"AS", L"ASDA", L"ASIA", L"ASSOCIATES", L"AT", L"ATHLETA", L"ATTORNEY", L"AU", L"AUCTION", L"AUDI", L"AUDIBLE", L"AUDIO", L"AUSPOST", L"AUTHOR", L"AUTO", L"AUTOS", L"AW", L"AWS", L"AX", L"AXA", L"AZ", L"AZURE", L"BA", L"BABY", L"BAIDU", L"BANAMEX", L"BAND", L"BANK", L"BAR", L"BARCELONA", L"BARCLAYCARD", L"BARCLAYS", L"BAREFOOT", L"BARGAINS", L"BASEBALL", L"BASKETBALL", L"BAUHAUS", L"BAYERN", L"BB", L"BBC", L"BBT", L"BBVA", L"BCG", L"BCN", L"BD", L"BE", L"BEATS", L"BEAUTY", L"BEER", L"BERLIN", L"BEST", L"BESTBUY", L"BET", L"BF", L"BG", L"BH", L"BHARTI", L"BI", L"BIBLE", L"BID", L"BIKE", L"BING", L"BINGO", L"BIO", L"BIZ", L"BJ", L"BLACK", L"BLACKFRIDAY", L"BLOCKBUSTER", L"BLOG", L"BLOOMBERG", L"BLUE", L"BM", L"BMS", L"BMW", L"BN", L"BNPPARIBAS", L"BO", L"BOATS", L"BOEHRINGER", L"BOFA", L"BOM", L"BOND", L"BOO", L"BOOK", L"BOOKING", L"BOSCH", L"BOSTIK", L"BOSTON", L"BOT", L"BOUTIQUE", L"BOX", L"BR", L"BRADESCO", L"BRIDGESTONE", L"BROADWAY", L"BROKER", L"BROTHER", L"BRUSSELS", L"BS", L"BT", L"BUILD", L"BUILDERS", L"BUSINESS", L"BUY", L"BUZZ", L"BV", L"BW", L"BY", L"BZ", L"BZH", L"CA", L"CAB", L"CAFE", L"CAL", L"CALL", L"CALVINKLEIN", L"CAM", L"CAMERA", L"CAMP", L"CANON", L"CAPETOWN", L"CAPITAL", L"CAPITALONE", L"CAR", L"CARAVAN", L"CARDS", L"CARE", L"CAREER", L"CAREERS", L"CARS", L"CASA", L"CASE", L"CASH", L"CASINO", L"CAT", L"CATERING", L"CATHOLIC", L"CBA", L"CBN", L"CBRE", L"CC", L"CD", L"CENTER", L"CEO", L"CERN", L"CF", L"CFA", L"CFD", L"CG", L"CH", L"CHANEL", L"CHANNEL", L"CHARITY", L"CHASE", L"CHAT", L"CHEAP", L"CHINTAI", L"CHRISTMAS", L"CHROME", L"CHURCH", L"CI", L"CIPRIANI", L"CIRCLE", L"CISCO", L"CITADEL", L"CITI", L"CITIC", L"CITY", L"CK", L"CL", L"CLAIMS", L"CLEANING", L"CLICK", L"CLINIC", L"CLINIQUE", L"CLOTHING", L"CLOUD", L"CLUB", L"CLUBMED", L"CM", L"CN", L"CO", L"COACH", L"CODES", L"COFFEE", L"COLLEGE", L"COLOGNE", L"COM", L"COMMBANK", L"COMMUNITY", L"COMPANY", L"COMPARE", L"COMPUTER", L"COMSEC", L"CONDOS", L"CONSTRUCTION", L"CONSULTING", L"CONTACT", L"CONTRACTORS", L"COOKING", L"COOL", L"COOP", L"CORSICA", L"COUNTRY", L"COUPON", L"COUPONS", L"COURSES", L"CPA", L"CR", L"CREDIT", L"CREDITCARD", L"CREDITUNION", L"CRICKET", L"CROWN", L"CRS", L"CRUISE", L"CRUISES", L"CU", L"CUISINELLA", L"CV", L"CW", L"CX", L"CY", L"CYMRU", L"CYOU", L"CZ", L"DAD", L"DANCE", L"DATA", L"DATE", L"DATING", L"DATSUN", L"DAY", L"DCLK", L"DDS", L"DE", L"DEAL", L"DEALER", L"DEALS", L"DEGREE", L"DELIVERY", L"DELL", L"DELOITTE", L"DELTA", L"DEMOCRAT", L"DENTAL", L"DENTIST", L"DESI", L"DESIGN", L"DEV", L"DHL", L"DIAMONDS", L"DIET", L"DIGITAL", L"DIRECT", L"DIRECTORY", L"DISCOUNT", L"DISCOVER", L"DISH", L"DIY", L"DJ", L"DK", L"DM", L"DNP", L"DO", L"DOCS", L"DOCTOR", L"DOG", L"DOMAINS", L"DOT", L"DOWNLOAD", L"DRIVE", L"DTV", L"DUBAI", L"DUNLOP", L"DUPONT", L"DURBAN", L"DVAG", L"DVR", L"DZ", L"EARTH", L"EAT", L"EC", L"ECO", L"EDEKA", L"EDU", L"EDUCATION", L"EE", L"EG", L"EMAIL", L"EMERCK", L"ENERGY", L"ENGINEER", L"ENGINEERING", L"ENTERPRISES", L"EPSON", L"EQUIPMENT", L"ER", L"ERICSSON", L"ERNI", L"ES", L"ESQ", L"ESTATE", L"ET", L"EU", L"EUROVISION", L"EUS", L"EVENTS", L"EXCHANGE", L"EXPERT", L"EXPOSED", L"EXPRESS", L"EXTRASPACE", L"FAGE", L"FAIL", L"FAIRWINDS", L"FAITH", L"FAMILY", L"FAN", L"FANS", L"FARM", L"FARMERS", L"FASHION", L"FAST", L"FEDEX", L"FEEDBACK", L"FERRARI", L"FERRERO", L"FI", L"FIDELITY", L"FIDO", L"FILM", L"FINAL", L"FINANCE", L"FINANCIAL", L"FIRE", L"FIRESTONE", L"FIRMDALE", L"FISH", L"FISHING", L"FIT", L"FITNESS", L"FJ", L"FK", L"FLICKR", L"FLIGHTS", L"FLIR", L"FLORIST", L"FLOWERS", L"FLY", L"FM", L"FO", L"FOO", L"FOOD", L"FOOTBALL", L"FORD", L"FOREX", L"FORSALE", L"FORUM", L"FOUNDATION", L"FOX", L"FR", L"FREE", L"FRESENIUS", L"FRL", L"FROGANS", L"FRONTIER", L"FTR", L"FUJITSU", L"FUN", L"FUND", L"FURNITURE", L"FUTBOL", L"FYI", L"GA", L"GAL", L"GALLERY", L"GALLO", L"GALLUP", L"GAME", L"GAMES", L"GAP", L"GARDEN", L"GAY", L"GB", L"GBIZ", L"GD", L"GDN", L"GE", L"GEA", L"GENT", L"GENTING", L"GEORGE", L"GF", L"GG", L"GGEE", L"GH", L"GI", L"GIFT", L"GIFTS", L"GIVES", L"GIVING", L"GL", L"GLASS", L"GLE", L"GLOBAL", L"GLOBO", L"GM", L"GMAIL", L"GMBH", L"GMO", L"GMX", L"GN", L"GODADDY", L"GOLD", L"GOLDPOINT", L"GOLF", L"GOO", L"GOODYEAR", L"GOOG", L"GOOGLE", L"GOP", L"GOT", L"GOV", L"GP", L"GQ", L"GR", L"GRAINGER", L"GRAPHICS", L"GRATIS", L"GREEN", L"GRIPE", L"GROCERY", L"GROUP", L"GS", L"GT", L"GU", L"GUCCI", L"GUGE", L"GUIDE", L"GUITARS", L"GURU", L"GW", L"GY", L"HAIR", L"HAMBURG", L"HANGOUT", L"HAUS", L"HBO", L"HDFC", L"HDFCBANK", L"HEALTH", L"HEALTHCARE", L"HELP", L"HELSINKI", L"HERE", L"HERMES", L"HIPHOP", L"HISAMITSU", L"HITACHI", L"HIV", L"HK", L"HKT", L"HM", L"HN", L"HOCKEY", L"HOLDINGS", L"HOLIDAY", L"HOMEDEPOT", L"HOMEGOODS", L"HOMES", L"HOMESENSE", L"HONDA", L"HORSE", L"HOSPITAL", L"HOST", L"HOSTING", L"HOT", L"HOTELS", L"HOTMAIL", L"HOUSE", L"HOW", L"HR", L"HSBC", L"HT", L"HU", L"HUGHES", L"HYATT", L"HYUNDAI", L"IBM", L"ICBC", L"ICE", L"ICU", L"ID", L"IE", L"IEEE", L"IFM", L"IKANO", L"IL", L"IM", L"IMAMAT", L"IMDB", L"IMMO", L"IMMOBILIEN", L"IN", L"INC", L"INDUSTRIES", L"INFINITI", L"INFO", L"ING", L"INK", L"INSTITUTE", L"INSURANCE", L"INSURE", L"INT", L"INTERNATIONAL", L"INTUIT", L"INVESTMENTS", L"IO", L"IPIRANGA", L"IQ", L"IR", L"IRISH", L"IS", L"ISMAILI", L"IST", L"ISTANBUL", L"IT", L"ITAU", L"ITV", L"JAGUAR", L"JAVA", L"JCB", L"JE", L"JEEP", L"JETZT", L"JEWELRY", L"JIO", L"JLL", L"JM", L"JMP", L"JNJ", L"JO", L"JOBS", L"JOBURG", L"JOT", L"JOY", L"JP", L"JPMORGAN", L"JPRS", L"JUEGOS", L"JUNIPER", L"KAUFEN", L"KDDI", L"KE", L"KERRYHOTELS", L"KERRYPROPERTIES", L"KFH", L"KG", L"KH", L"KI", L"KIA", L"KIDS", L"KIM", L"KINDLE", L"KITCHEN", L"KIWI", L"KM", L"KN", L"KOELN", L"KOMATSU", L"KOSHER", L"KP", L"KPMG", L"KPN", L"KR", L"KRD", L"KRED", L"KUOKGROUP", L"KW", L"KY", L"KYOTO", L"KZ", L"LA", L"LACAIXA", L"LAMBORGHINI", L"LAMER", L"LAND", L"LANDROVER", L"LANXESS", L"LASALLE", L"LAT", L"LATINO", L"LATROBE", L"LAW", L"LAWYER", L"LB", L"LC", L"LDS", L"LEASE", L"LECLERC", L"LEFRAK", L"LEGAL", L"LEGO", L"LEXUS", L"LGBT", L"LI", L"LIDL", L"LIFE", L"LIFEINSURANCE", L"LIFESTYLE", L"LIGHTING", L"LIKE", L"LILLY", L"LIMITED", L"LIMO", L"LINCOLN", L"LINK", L"LIVE", L"LIVING", L"LK", L"LLC", L"LLP", L"LOAN", L"LOANS", L"LOCKER", L"LOCUS", L"LOL", L"LONDON", L"LOTTE", L"LOTTO", L"LOVE", L"LPL", L"LPLFINANCIAL", L"LR", L"LS", L"LT", L"LTD", L"LTDA", L"LU", L"LUNDBECK", L"LUXE", L"LUXURY", L"LV", L"LY", L"MA", L"MADRID", L"MAIF", L"MAISON", L"MAKEUP", L"MAN", L"MANAGEMENT", L"MANGO", L"MAP", L"MARKET", L"MARKETING", L"MARKETS", L"MARRIOTT", L"MARSHALLS", L"MATTEL", L"MBA", L"MC", L"MCKINSEY", L"MD", L"ME", L"MED", L"MEDIA", L"MEET", L"MELBOURNE", L"MEME", L"MEMORIAL", L"MEN", L"MENU", L"MERCKMSD", L"MG", L"MH", L"MIAMI", L"MICROSOFT", L"MIL", L"MINI", L"MINT", L"MIT", L"MITSUBISHI", L"MK", L"ML", L"MLB", L"MLS", L"MM", L"MMA", L"MN", L"MO", L"MOBI", L"MOBILE", L"MODA", L"MOE", L"MOI", L"MOM", L"MONASH", L"MONEY", L"MONSTER", L"MORMON", L"MORTGAGE", L"MOSCOW", L"MOTO", L"MOTORCYCLES", L"MOV", L"MOVIE", L"MP", L"MQ", L"MR", L"MS", L"MSD", L"MT", L"MTN", L"MTR", L"MU", L"MUSEUM", L"MUSIC", L"MV", L"MW", L"MX", L"MY", L"MZ", L"NA", L"NAB", L"NAGOYA", L"NAME", L"NAVY", L"NBA", L"NC", L"NE", L"NEC", L"NET", L"NETBANK", L"NETFLIX", L"NETWORK", L"NEUSTAR", L"NEW", L"NEWS", L"NEXT", L"NEXTDIRECT", L"NEXUS", L"NF", L"NFL", L"NG", L"NGO", L"NHK", L"NI", L"NICO", L"NIKE", L"NIKON", L"NINJA", L"NISSAN", L"NISSAY", L"NL", L"NO", L"NOKIA", L"NORTON", L"NOW", L"NOWRUZ", L"NOWTV", L"NP", L"NR", L"NRA", L"NRW", L"NTT", L"NU", L"NYC", L"NZ", L"OBI", L"OBSERVER", L"OFFICE", L"OKINAWA", L"OLAYAN", L"OLAYANGROUP", L"OLLO", L"OM", L"OMEGA", L"ONE", L"ONG", L"ONL", L"ONLINE", L"OOO", L"OPEN", L"ORACLE", L"ORANGE", L"ORG", L"ORGANIC", L"ORIGINS", L"OSAKA", L"OTSUKA", L"OTT", L"OVH", L"PA", L"PAGE", L"PANASONIC", L"PARIS", L"PARS", L"PARTNERS", L"PARTS", L"PARTY", L"PAY", L"PCCW", L"PE", L"PET", L"PF", L"PFIZER", L"PG", L"PH", L"PHARMACY", L"PHD", L"PHILIPS", L"PHONE", L"PHOTO", L"PHOTOGRAPHY", L"PHOTOS", L"PHYSIO", L"PICS", L"PICTET", L"PICTURES", L"PID", L"PIN", L"PING", L"PINK", L"PIONEER", L"PIZZA", L"PK", L"PL", L"PLACE", L"PLAY", L"PLAYSTATION", L"PLUMBING", L"PLUS", L"PM", L"PN", L"PNC", L"POHL", L"POKER", L"POLITIE", L"PORN", L"POST", L"PR", L"PRAXI", L"PRESS", L"PRIME", L"PRO", L"PROD", L"PRODUCTIONS", L"PROF", L"PROGRESSIVE", L"PROMO", L"PROPERTIES", L"PROPERTY", L"PROTECTION", L"PRU", L"PRUDENTIAL", L"PS", L"PT", L"PUB", L"PW", L"PWC", L"PY", L"QA", L"QPON", L"QUEBEC", L"QUEST", L"RACING", L"RADIO", L"RE", L"READ", L"REALESTATE", L"REALTOR", L"REALTY", L"RECIPES", L"RED", L"REDSTONE", L"REDUMBRELLA", L"REHAB", L"REISE", L"REISEN", L"REIT", L"RELIANCE", L"REN", L"RENT", L"RENTALS", L"REPAIR", L"REPORT", L"REPUBLICAN", L"REST", L"RESTAURANT", L"REVIEW", L"REVIEWS", L"REXROTH", L"RICH", L"RICHARDLI", L"RICOH", L"RIL", L"RIO", L"RIP", L"RO", L"ROCKS", L"RODEO", L"ROGERS", L"ROOM", L"RS", L"RSVP", L"RU", L"RUGBY", L"RUHR", L"RUN", L"RW", L"RWE", L"RYUKYU", L"SA", L"SAARLAND", L"SAFE", L"SAFETY", L"SAKURA", L"SALE", L"SALON", L"SAMSCLUB", L"SAMSUNG", L"SANDVIK", L"SANDVIKCOROMANT", L"SANOFI", L"SAP", L"SARL", L"SAS", L"SAVE", L"SAXO", L"SB", L"SBI", L"SBS", L"SC", L"SCB", L"SCHAEFFLER", L"SCHMIDT", L"SCHOLARSHIPS", L"SCHOOL", L"SCHULE", L"SCHWARZ", L"SCIENCE", L"SCOT", L"SD", L"SE", L"SEARCH", L"SEAT", L"SECURE", L"SECURITY", L"SEEK", L"SELECT", L"SENER", L"SERVICES", L"SEVEN", L"SEW", L"SEX", L"SEXY", L"SFR", L"SG", L"SH", L"SHANGRILA", L"SHARP", L"SHELL", L"SHIA", L"SHIKSHA", L"SHOES", L"SHOP", L"SHOPPING", L"SHOUJI", L"SHOW", L"SI", L"SILK", L"SINA", L"SINGLES", L"SITE", L"SJ", L"SK", L"SKI", L"SKIN", L"SKY", L"SKYPE", L"SL", L"SLING", L"SM", L"SMART", L"SMILE", L"SN", L"SNCF", L"SO", L"SOCCER", L"SOCIAL", L"SOFTBANK", L"SOFTWARE", L"SOHU", L"SOLAR", L"SOLUTIONS", L"SONG", L"SONY", L"SOY", L"SPA", L"SPACE", L"SPORT", L"SPOT", L"SR", L"SRL", L"SS", L"ST", L"STADA", L"STAPLES", L"STAR", L"STATEBANK", L"STATEFARM", L"STC", L"STCGROUP", L"STOCKHOLM", L"STORAGE", L"STORE", L"STREAM", L"STUDIO", L"STUDY", L"STYLE", L"SU", L"SUCKS", L"SUPPLIES", L"SUPPLY", L"SUPPORT", L"SURF", L"SURGERY", L"SUZUKI", L"SV", L"SWATCH", L"SWISS", L"SX", L"SY", L"SYDNEY", L"SYSTEMS", L"SZ", L"TAB", L"TAIPEI", L"TALK", L"TAOBAO", L"TARGET", L"TATAMOTORS", L"TATAR", L"TATTOO", L"TAX", L"TAXI", L"TC", L"TCI", L"TD", L"TDK", L"TEAM", L"TECH", L"TECHNOLOGY", L"TEL", L"TEMASEK", L"TENNIS", L"TEVA", L"TF", L"TG", L"TH", L"THD", L"THEATER", L"THEATRE", L"TIAA", L"TICKETS", L"TIENDA", L"TIPS", L"TIRES", L"TIROL", L"TJ", L"TJMAXX", L"TJX", L"TK", L"TKMAXX", L"TL", L"TM", L"TMALL", L"TN", L"TO", L"TODAY", L"TOKYO", L"TOOLS", L"TOP", L"TORAY", L"TOSHIBA", L"TOTAL", L"TOURS", L"TOWN", L"TOYOTA", L"TOYS", L"TR", L"TRADE", L"TRADING", L"TRAINING", L"TRAVEL", L"TRAVELERS", L"TRAVELERSINSURANCE", L"TRUST", L"TRV", L"TT", L"TUBE", L"TUI", L"TUNES", L"TUSHU", L"TV", L"TVS", L"TW", L"TZ", L"UA", L"UBANK", L"UBS", L"UG", L"UK", L"UNICOM", L"UNIVERSITY", L"UNO", L"UOL", L"UPS", L"US", L"UY", L"UZ", L"VA", L"VACATIONS", L"VANA", L"VANGUARD", L"VC", L"VE", L"VEGAS", L"VENTURES", L"VERISIGN", L"VERSICHERUNG", L"VET", L"VG", L"VI", L"VIAJES", L"VIDEO", L"VIG", L"VIKING", L"VILLAS", L"VIN", L"VIP", L"VIRGIN", L"VISA", L"VISION", L"VIVA", L"VIVO", L"VLAANDEREN", L"VN", L"VODKA", L"VOLVO", L"VOTE", L"VOTING", L"VOTO", L"VOYAGE", L"VU", L"WALES", L"WALMART", L"WALTER", L"WANG", L"WANGGOU", L"WATCH", L"WATCHES", L"WEATHER", L"WEATHERCHANNEL", L"WEBCAM", L"WEBER", L"WEBSITE", L"WED", L"WEDDING", L"WEIBO", L"WEIR", L"WF", L"WHOSWHO", L"WIEN", L"WIKI", L"WILLIAMHILL", L"WIN", L"WINDOWS", L"WINE", L"WINNERS", L"WME", L"WOLTERSKLUWER", L"WOODSIDE", L"WORK", L"WORKS", L"WORLD", L"WOW", L"WS", L"WTC", L"WTF", L"XBOX", L"XEROX", L"XIHUAN", L"XIN", L"XN--11B4C3D", L"XN--1CK2E1B", L"XN--1QQW23A", L"XN--2SCRJ9C", L"XN--30RR7Y", L"XN--3BST00M", L"XN--3DS443G", L"XN--3E0B707E", L"XN--3HCRJ9C", L"XN--3PXU8K", L"XN--42C2D9A", L"XN--45BR5CYL", L"XN--45BRJ9C", L"XN--45Q11C", L"XN--4DBRK0CE", L"XN--4GBRIM", L"XN--54B7FTA0CC", L"XN--55QW42G", L"XN--55QX5D", L"XN--5SU34J936BGSG", L"XN--5TZM5G", L"XN--6FRZ82G", L"XN--6QQ986B3XL", L"XN--80ADXHKS", L"XN--80AO21A", L"XN--80AQECDR1A", L"XN--80ASEHDB", L"XN--80ASWG", L"XN--8Y0A063A", L"XN--90A3AC", L"XN--90AE", L"XN--90AIS", L"XN--9DBQ2A", L"XN--9ET52U", L"XN--9KRT00A", L"XN--B4W605FERD", L"XN--BCK1B9A5DRE4C", L"XN--C1AVG", L"XN--C2BR7G", L"XN--CCK2B3B", L"XN--CCKWCXETD", L"XN--CG4BKI", L"XN--CLCHC0EA0B2G2A9GCD", L"XN--CZR694B", L"XN--CZRS0T", L"XN--CZRU2D", L"XN--D1ACJ3B", L"XN--D1ALF", L"XN--E1A4C", L"XN--ECKVDTC9D", L"XN--EFVY88H", L"XN--FCT429K", L"XN--FHBEI", L"XN--FIQ228C5HS", L"XN--FIQ64B", L"XN--FIQS8S", L"XN--FIQZ9S", L"XN--FJQ720A", L"XN--FLW351E", L"XN--FPCRJ9C3D", L"XN--FZC2C9E2C", L"XN--FZYS8D69UVGM", L"XN--G2XX48C", L"XN--GCKR3F0F", L"XN--GECRJ9C", L"XN--GK3AT1E", L"XN--H2BREG3EVE", L"XN--H2BRJ9C", L"XN--H2BRJ9C8C", L"XN--HXT814E", L"XN--I1B6B1A6A2E", L"XN--IMR513N", L"XN--IO0A7I", L"XN--J1AEF", L"XN--J1AMH", L"XN--J6W193G", L"XN--JLQ480N2RG", L"XN--JVR189M", L"XN--KCRX77D1X4A", L"XN--KPRW13D", L"XN--KPRY57D", L"XN--KPUT3I", L"XN--L1ACC", L"XN--LGBBAT1AD8J", L"XN--MGB9AWBF", L"XN--MGBA3A3EJT", L"XN--MGBA3A4F16A", L"XN--MGBA7C0BBN0A", L"XN--MGBAAM7A8H", L"XN--MGBAB2BD", L"XN--MGBAH1A3HJKRD", L"XN--MGBAI9AZGQP6J", L"XN--MGBAYH7GPA", L"XN--MGBBH1A", L"XN--MGBBH1A71E", L"XN--MGBC0A9AZCG", L"XN--MGBCA7DZDO", L"XN--MGBCPQ6GPA1A", L"XN--MGBERP4A5D4AR", L"XN--MGBGU82A", L"XN--MGBI4ECEXP", L"XN--MGBPL2FH", L"XN--MGBT3DHD", L"XN--MGBTX2B", L"XN--MGBX4CD0AB", L"XN--MIX891F", L"XN--MK1BU44C", L"XN--MXTQ1M", L"XN--NGBC5AZD", L"XN--NGBE9E0A", L"XN--NGBRX", L"XN--NODE", L"XN--NQV7F", L"XN--NQV7FS00EMA", L"XN--NYQY26A", L"XN--O3CW4H", L"XN--OGBPF8FL", L"XN--OTU796D", L"XN--P1ACF", L"XN--P1AI", L"XN--PGBS0DH", L"XN--PSSY2U", L"XN--Q7CE6A", L"XN--Q9JYB4C", L"XN--QCKA1PMC", L"XN--QXA6A", L"XN--QXAM", L"XN--RHQV96G", L"XN--ROVU88B", L"XN--RVC1E0AM3E", L"XN--S9BRJ9C", L"XN--SES554G", L"XN--T60B56A", L"XN--TCKWE", L"XN--TIQ49XQYJ", L"XN--UNUP4Y", L"XN--VERMGENSBERATER-CTB", L"XN--VERMGENSBERATUNG-PWB", L"XN--VHQUV", L"XN--VUQ861B", L"XN--W4R85EL8FHU5DNRA", L"XN--W4RS40L", L"XN--WGBH1C", L"XN--WGBL6A", L"XN--XHQ521B", L"XN--XKC2AL3HYE2A", L"XN--XKC2DL3A5EE0H", L"XN--Y9A3AQ", L"XN--YFRO4I67O", L"XN--YGBI2AMMX", L"XN--ZFR164B", L"XXX", L"XYZ", L"YACHTS", L"YAHOO", L"YAMAXUN", L"YANDEX", L"YE", L"YODOBASHI", L"YOGA", L"YOKOHAMA", L"YOU", L"YOUTUBE", L"YT", L"YUN", L"ZA", L"ZAPPOS", L"ZARA", L"ZERO", L"ZIP", L"ZM", L"ZONE", L"ZUERICH", L"ZW", };

    //cia kodas biski goofy, biski mano sizofrenijos, biski chatuko nesamoniu
    std::wstring zodis;
    while (eilute >> zodis) {
        if (zodis.find(L'.') != std::wstring::npos) {
            std::vector<std::wstring> segments;
            std::wstring segment;

            // Build segments by splitting on separators
            for (size_t i = 0; i < zodis.length(); ++i) {
                if (zodis[i] == L'.' || zodis[i] == L'/' || zodis[i] == L':') {
                    if (!segment.empty()) {
                        segments.push_back(segment);
                        segment.clear();
                    }
                } else {
                    segment += zodis[i];
                }
            }

            // Add the last segment if it's not empty
            if (!segment.empty()) {
                segments.push_back(segment);
            }

            // Check if any segment is a TLD
            bool isLink = false;
            for (const auto& seg : segments) {
                // Convert to uppercase for TLD comparison
                std::wstring upperSeg = seg;
                std::transform(upperSeg.begin(), upperSeg.end(), upperSeg.begin(), ::towupper);

                if (!seg.empty() && tlds.contains(upperSeg)) {
                    isLink = true;
                    break;
                }
            }

            if (isLink) {
                links.push_back(zodis);
            }
        }
    }
}

void input(RBTreeMap<std::wstring>& Tree, std::vector<std::wstring>& links , const std::string& input) {
    // Lietuviskos raides ir tam tikri lt simboliai neveikia normaliai, nes mingw c++20 nesupportina utc-8 normaliai. whatever
    try {
        std::locale::global(std::locale("lt-LT"));
    } catch (std::runtime_error& e) {
        std::cout << "Tarptautinės raidės gali veikti neteisingai" << e.what() << std::endl;
    }

    std::wifstream in{input};
    if (!in || !in.is_open()) {
        std::cerr<<"Failas nerastas"<<std::endl;
        throw std::runtime_error("Failed to open file");
    }

    in.imbue(std::locale());

    std::wstring line;
    int lineNumber = 1;

    while (std::getline(in, line)) {
        std::wstringstream lineStream(line);
        std::wstringstream linkStream(lineStream.str());
        link_apdorojimas(links, linkStream);
        eilutes_apdorojimas(lineStream);

        std::wstring zodis;
        int zodzioNumber{1};
        while (lineStream >> zodis) {
            Tree.insert(zodis, lineNumber, zodzioNumber);
            zodzioNumber++;
        }

        lineNumber++;
    }

    in.close();
}
