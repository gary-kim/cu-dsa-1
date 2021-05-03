// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <iterator>
#include <unordered_map>
#include <vector>

unordered_map<string, unsigned int> lastNamesOrdered = {
    {"ACOSTA", 0},       {"ADAMS", 1},        {"ADKINS", 2},
    {"AGUILAR", 3},      {"AGUIRRE", 4},      {"ALEXANDER", 5},
    {"ALLEN", 6},        {"ALVARADO", 7},     {"ALVAREZ", 8},
    {"ANDERSON", 9},     {"ANDREWS", 10},     {"ARMSTRONG", 11},
    {"ARNOLD", 12},      {"AUSTIN", 13},      {"AVILA", 14},
    {"AYALA", 15},       {"BAILEY", 16},      {"BAKER", 17},
    {"BALDWIN", 18},     {"BANKS", 19},       {"BARBER", 20},
    {"BARKER", 21},      {"BARNES", 22},      {"BARNETT", 23},
    {"BARRETT", 24},     {"BARTON", 25},      {"BATES", 26},
    {"BECK", 27},        {"BECKER", 28},      {"BELL", 29},
    {"BENNETT", 30},     {"BENSON", 31},      {"BERRY", 32},
    {"BISHOP", 33},      {"BLACK", 34},       {"BLAIR", 35},
    {"BLAKE", 36},       {"BOWEN", 37},       {"BOWMAN", 38},
    {"BOYD", 39},        {"BRADLEY", 40},     {"BRADY", 41},
    {"BREWER", 42},      {"BROOKS", 43},      {"BROWN", 44},
    {"BRYANT", 45},      {"BURGESS", 46},     {"BURKE", 47},
    {"BURNS", 48},       {"BURTON", 49},      {"BUSH", 50},
    {"BUTLER", 51},      {"BYRD", 52},        {"CABRERA", 53},
    {"CALDERON", 54},    {"CALDWELL", 55},    {"CAMACHO", 56},
    {"CAMPBELL", 57},    {"CAMPOS", 58},      {"CANNON", 59},
    {"CARDENAS", 60},    {"CARLSON", 61},     {"CARPENTER", 62},
    {"CARR", 63},        {"CARRILLO", 64},    {"CARROLL", 65},
    {"CARTER", 66},      {"CASTANEDA", 67},   {"CASTILLO", 68},
    {"CASTRO", 69},      {"CERVANTES", 70},   {"CHAMBERS", 71},
    {"CHAN", 72},        {"CHANDLER", 73},    {"CHANG", 74},
    {"CHAPMAN", 75},     {"CHAVEZ", 76},      {"CHEN", 77},
    {"CHRISTENSEN", 78}, {"CLARK", 79},       {"CLARKE", 80},
    {"COHEN", 81},       {"COLE", 82},        {"COLEMAN", 83},
    {"COLLINS", 84},     {"COLON", 85},       {"CONTRERAS", 86},
    {"COOK", 87},        {"COOPER", 88},      {"CORTEZ", 89},
    {"COX", 90},         {"CRAIG", 91},       {"CRAWFORD", 92},
    {"CROSS", 93},       {"CRUZ", 94},        {"CUMMINGS", 95},
    {"CUNNINGHAM", 96},  {"CURRY", 97},       {"CURTIS", 98},
    {"DANIEL", 99},      {"DANIELS", 100},    {"DAVIDSON", 101},
    {"DAVIS", 102},      {"DAWSON", 103},     {"DAY", 104},
    {"DEAN", 105},       {"DELACRUZ", 106},   {"DELEON", 107},
    {"DELGADO", 108},    {"DENNIS", 109},     {"DIAZ", 110},
    {"DIXON", 111},      {"DOMINGUEZ", 112},  {"DOUGLAS", 113},
    {"DOYLE", 114},      {"DUNCAN", 115},     {"DUNN", 116},
    {"DURAN", 117},      {"EDWARDS", 118},    {"ELLIOTT", 119},
    {"ELLIS", 120},      {"ERICKSON", 121},   {"ESPINOZA", 122},
    {"ESTRADA", 123},    {"EVANS", 124},      {"FARMER", 125},
    {"FERGUSON", 126},   {"FERNANDEZ", 127},  {"FIELDS", 128},
    {"FIGUEROA", 129},   {"FISCHER", 130},    {"FISHER", 131},
    {"FITZGERALD", 132}, {"FLEMING", 133},    {"FLETCHER", 134},
    {"FLORES", 135},     {"FORD", 136},       {"FOSTER", 137},
    {"FOWLER", 138},     {"FOX", 139},        {"FRANCIS", 140},
    {"FRANCO", 141},     {"FRANK", 142},      {"FRANKLIN", 143},
    {"FRAZIER", 144},    {"FREEMAN", 145},    {"FUENTES", 146},
    {"FULLER", 147},     {"GALLAGHER", 148},  {"GALLEGOS", 149},
    {"GARCIA", 150},     {"GARDNER", 151},    {"GARNER", 152},
    {"GARRETT", 153},    {"GARZA", 154},      {"GEORGE", 155},
    {"GIBSON", 156},     {"GILBERT", 157},    {"GILL", 158},
    {"GOMEZ", 159},      {"GONZALES", 160},   {"GONZALEZ", 161},
    {"GOODMAN", 162},    {"GOODWIN", 163},    {"GORDON", 164},
    {"GRAHAM", 165},     {"GRANT", 166},      {"GRAVES", 167},
    {"GRAY", 168},       {"GREEN", 169},      {"GREENE", 170},
    {"GREGORY", 171},    {"GRIFFIN", 172},    {"GRIFFITH", 173},
    {"GROSS", 174},      {"GUERRA", 175},     {"GUERRERO", 176},
    {"GUTIERREZ", 177},  {"GUZMAN", 178},     {"HAIL", 179},
    {"HALE", 180},       {"HALL", 181},       {"HAMILTON", 182},
    {"HAMMOND", 183},    {"HAMPTON", 184},    {"HANSEN", 185},
    {"HANSON", 186},     {"HARDY", 187},      {"HARMON", 188},
    {"HARPER", 189},     {"HARRINGTON", 190}, {"HARRIS", 191},
    {"HARRISON", 192},   {"HART", 193},       {"HARVEY", 194},
    {"HAWKINS", 195},    {"HAYES", 196},      {"HAYNES", 197},
    {"HENDERSON", 198},  {"HENRY", 199},      {"HERNANDEZ", 200},
    {"HERRERA", 201},    {"HICKS", 202},      {"HIGGINS", 203},
    {"HILL", 204},       {"HINES", 205},      {"HODGES", 206},
    {"HOFFMAN", 207},    {"HOLLAND", 208},    {"HOLMES", 209},
    {"HOLT", 210},       {"HOPKINS", 211},    {"HORTON", 212},
    {"HOWARD", 213},     {"HOWELL", 214},     {"HUANG", 215},
    {"HUBBARD", 216},    {"HUDSON", 217},     {"HUGHES", 218},
    {"HUNT", 219},       {"HUNTER", 220},     {"INGRAM", 221},
    {"JACKSON", 222},    {"JACOBS", 223},     {"JAMES", 224},
    {"JENKINS", 225},    {"JENNINGS", 226},   {"JENSEN", 227},
    {"JIMENEZ", 228},    {"JOHNSON", 229},    {"JOHNSTON", 230},
    {"JONES", 231},      {"JORDAN", 232},     {"JOSEPH", 233},
    {"JUAREZ", 234},     {"KELLER", 235},     {"KELLEY", 236},
    {"KELLY", 237},      {"KENNEDY", 238},    {"KHAN", 239},
    {"KIM", 240},        {"KING", 241},       {"KLEIN", 242},
    {"KNIGHT", 243},     {"LAMBERT", 244},    {"LANE", 245},
    {"LARA", 246},       {"LARSON", 247},     {"LAWRENCE", 248},
    {"LAWSON", 249},     {"LE", 250},         {"LEE", 251},
    {"LEON", 252},       {"LEONARD", 253},    {"LEWIS", 254},
    {"LI", 255},         {"LIN", 256},        {"LITTLE", 257},
    {"LIU", 258},        {"LOGAN", 259},      {"LONG", 260},
    {"LOPEZ", 261},      {"LOVE", 262},       {"LOWE", 263},
    {"LUCAS", 264},      {"LUNA", 265},       {"LYNCH", 266},
    {"LYONS", 267},      {"MACK", 268},       {"MALDONADO", 269},
    {"MALONE", 270},     {"MANN", 271},       {"MANNING", 272},
    {"MARQUEZ", 273},    {"MARSHALL", 274},   {"MARTIN", 275},
    {"MARTINEZ", 276},   {"MASON", 277},      {"MATTHEWS", 278},
    {"MAXWELL", 279},    {"MAY", 280},        {"MCCARTHY", 281},
    {"MCCOY", 282},      {"MCDANIEL", 283},   {"MCDONALD", 284},
    {"MCGEE", 285},      {"MCKINNEY", 286},   {"MCLAUGHLIN", 287},
    {"MEDINA", 288},     {"MEJIA", 289},      {"MENDEZ", 290},
    {"MENDOZA", 291},    {"MEYER", 292},      {"MILES", 293},
    {"MILLER", 294},     {"MILLS", 295},      {"MIRANDA", 296},
    {"MITCHELL", 297},   {"MOLINA", 298},     {"MONTGOMERY", 299},
    {"MONTOYA", 300},    {"MOORE", 301},      {"MORALES", 302},
    {"MORAN", 303},      {"MORENO", 304},     {"MORGAN", 305},
    {"MORRIS", 306},     {"MORRISON", 307},   {"MOSS", 308},
    {"MULLINS", 309},    {"MUNOZ", 310},      {"MURPHY", 311},
    {"MURRAY", 312},     {"MYERS", 313},      {"NAVARRO", 314},
    {"NEAL", 315},       {"NELSON", 316},     {"NEWMAN", 317},
    {"NEWTON", 318},     {"NGUYEN", 319},     {"NICHOLS", 320},
    {"NORMAN", 321},     {"NORRIS", 322},     {"NUNEZ", 323},
    {"OBRIEN", 324},     {"OCHOA", 325},      {"OCONNOR", 326},
    {"OLIVER", 327},     {"OLSON", 328},      {"ORTEGA", 329},
    {"ORTIZ", 330},      {"OWENS", 331},      {"PACHECO", 332},
    {"PADILLA", 333},    {"PAGE", 334},       {"PALMER", 335},
    {"PARK", 336},       {"PARKER", 337},     {"PARKS", 338},
    {"PARSONS", 339},    {"PATEL", 340},      {"PATTERSON", 341},
    {"PAUL", 342},       {"PAYNE", 343},      {"PEARSON", 344},
    {"PENA", 345},       {"PEREZ", 346},      {"PERKINS", 347},
    {"PERRY", 348},      {"PERSON", 349},     {"PETERS", 350},
    {"PETERSON", 351},   {"PHAM", 352},       {"PHILLIPS", 353},
    {"PIERCE", 354},     {"PORTER", 355},     {"POTTER", 356},
    {"POWELL", 357},     {"POWERS", 358},     {"PRICE", 359},
    {"QUINN", 360},      {"RAMIREZ", 361},    {"RAMOS", 362},
    {"RAMSEY", 363},     {"RAY", 364},        {"REED", 365},
    {"REESE", 366},      {"REEVES", 367},     {"REID", 368},
    {"REYES", 369},      {"REYNOLDS", 370},   {"RHODES", 371},
    {"RICE", 372},       {"RICHARDS", 373},   {"RICHARDSON", 374},
    {"RILEY", 375},      {"RIOS", 376},       {"RIVAS", 377},
    {"RIVERA", 378},     {"ROBBINS", 379},    {"ROBERTS", 380},
    {"ROBERTSON", 381},  {"ROBINSON", 382},   {"ROBLES", 383},
    {"RODGERS", 384},    {"RODRIGUEZ", 385},  {"ROGERS", 386},
    {"ROJAS", 387},      {"ROMAN", 388},      {"ROMERO", 389},
    {"ROSALES", 390},    {"ROSE", 391},       {"ROSS", 392},
    {"ROWE", 393},       {"RUIZ", 394},       {"RUSSELL", 395},
    {"RYAN", 396},       {"SALAZAR", 397},    {"SALINAS", 398},
    {"SANCHEZ", 399},    {"SANDERS", 400},    {"SANDOVAL", 401},
    {"SANTIAGO", 402},   {"SANTOS", 403},     {"SAUNDERS", 404},
    {"SCHMIDT", 405},    {"SCHNEIDER", 406},  {"SCHROEDER", 407},
    {"SCHULTZ", 408},    {"SCHWARTZ", 409},   {"SCOTT", 410},
    {"SERRANO", 411},    {"SHARP", 412},      {"SHAW", 413},
    {"SHELTON", 414},    {"SHERMAN", 415},    {"SILVA", 416},
    {"SIMMONS", 417},    {"SIMON", 418},      {"SIMPSON", 419},
    {"SIMS", 420},       {"SINGH", 421},      {"SMITH", 422},
    {"SNYDER", 423},     {"SOLIS", 424},      {"SOTO", 425},
    {"SPENCER", 426},    {"STANLEY", 427},    {"STEELE", 428},
    {"STEPHENS", 429},   {"STEVENS", 430},    {"STEVENSON", 431},
    {"STEWART", 432},    {"STONE", 433},      {"STRICKLAND", 434},
    {"SULLIVAN", 435},   {"SUTTON", 436},     {"SWANSON", 437},
    {"TATE", 438},       {"TAYLOR", 439},     {"TERRY", 440},
    {"THOMAS", 441},     {"THOMPSON", 442},   {"THORNTON", 443},
    {"TODD", 444},       {"TORRES", 445},     {"TOWNSEND", 446},
    {"TRAN", 447},       {"TRUJILLO", 448},   {"TUCKER", 449},
    {"TURNER", 450},     {"VALDEZ", 451},     {"VALENCIA", 452},
    {"VARGAS", 453},     {"VASQUEZ", 454},    {"VAUGHN", 455},
    {"VAZQUEZ", 456},    {"VEGA", 457},       {"VELASQUEZ", 458},
    {"WADE", 459},       {"WAGNER", 460},     {"WALKER", 461},
    {"WALLACE", 462},    {"WALSH", 463},      {"WALTERS", 464},
    {"WALTON", 465},     {"WANG", 466},       {"WARD", 467},
    {"WARNER", 468},     {"WARREN", 469},     {"WASHINGTON", 470},
    {"WATERS", 471},     {"WATKINS", 472},    {"WATSON", 473},
    {"WATTS", 474},      {"WEAVER", 475},     {"WEBB", 476},
    {"WEBER", 477},      {"WEBSTER", 478},    {"WELCH", 479},
    {"WELLS", 480},      {"WEST", 481},       {"WHEELER", 482},
    {"WHITE", 483},      {"WILLIAMS", 484},   {"WILLIAMSON", 485},
    {"WILLIS", 486},     {"WILSON", 487},     {"WISE", 488},
    {"WOLF", 489},       {"WOLFE", 490},      {"WONG", 491},
    {"WOOD", 492},       {"WOODS", 493},      {"WRIGHT", 494},
    {"WU", 495},         {"YANG", 496},       {"YOUNG", 497},
    {"ZHANG", 498},      {"ZIMMERMAN", 499}};

unordered_map<string, unsigned int> firstNamesOrdered = {
    {"AALIYAH", 0},     {"AARON", 1},       {"ABEL", 2},
    {"ABIGAIL", 3},     {"ABRAHAM", 4},     {"ADALINE", 5},
    {"ADALYN", 6},      {"ADALYNN", 7},     {"ADAM", 8},
    {"ADDISON", 9},     {"ADELINE", 10},    {"ADELYN", 11},
    {"ADRIAN", 12},     {"ADRIANA", 13},    {"AIDAN", 14},
    {"AIDEN", 15},      {"ALAINA", 16},     {"ALAN", 17},
    {"ALANA", 18},      {"ALAYNA", 19},     {"ALEJANDRO", 20},
    {"ALEX", 21},       {"ALEXA", 22},      {"ALEXANDER", 23},
    {"ALEXANDRA", 24},  {"ALEXIS", 25},     {"ALICE", 26},
    {"ALINA", 27},      {"ALIVIA", 28},     {"ALIYAH", 29},
    {"ALLISON", 30},    {"ALYSSA", 31},     {"AMARA", 32},
    {"AMAYA", 33},      {"AMELIA", 34},     {"AMIR", 35},
    {"AMY", 36},        {"ANA", 37},        {"ANASTASIA", 38},
    {"ANDREA", 39},     {"ANDRES", 40},     {"ANDREW", 41},
    {"ANGEL", 42},      {"ANGELA", 43},     {"ANGELINA", 44},
    {"ANNA", 45},       {"ANNABELLE", 46},  {"ANTHONY", 47},
    {"ANTONIO", 48},    {"ARABELLA", 49},   {"ARIA", 50},
    {"ARIANA", 51},     {"ARIANNA", 52},    {"ARIEL", 53},
    {"ARTHUR", 54},     {"ARYA", 55},       {"ASHER", 56},
    {"ASHLEY", 57},     {"ASHTON", 58},     {"ATHENA", 59},
    {"AUBREE", 60},     {"AUBREY", 61},     {"AUDREY", 62},
    {"AUGUST", 63},     {"AURORA", 64},     {"AUSTIN", 65},
    {"AUTUMN", 66},     {"AVA", 67},        {"AVERY", 68},
    {"AXEL", 69},       {"AYDEN", 70},      {"AYLA", 71},
    {"BAILEY", 72},     {"BARRETT", 73},    {"BEAU", 74},
    {"BECKETT", 75},    {"BELLA", 76},      {"BENJAMIN", 77},
    {"BENNETT", 78},    {"BENTLEY", 79},    {"BLAKE", 80},
    {"BRADLEY", 81},    {"BRADY", 82},      {"BRANDON", 83},
    {"BRANTLEY", 84},   {"BRAXTON", 85},    {"BRAYDEN", 86},
    {"BRIAN", 87},      {"BRIANNA", 88},    {"BRIELLE", 89},
    {"BRODY", 90},      {"BROOKE", 91},     {"BROOKLYN", 92},
    {"BROOKLYNN", 93},  {"BROOKS", 94},     {"BRYAN", 95},
    {"BRYCE", 96},      {"BRYNLEE", 97},    {"BRYSON", 98},
    {"CADEN", 99},      {"CALEB", 100},     {"CALLIE", 101},
    {"CALVIN", 102},    {"CAMDEN", 103},    {"CAMERON", 104},
    {"CAMILA", 105},    {"CARLOS", 106},    {"CAROLINE", 107},
    {"CARSON", 108},    {"CARTER", 109},    {"CATHERINE", 110},
    {"CAYDEN", 111},    {"CECILIA", 112},   {"CHARLES", 113},
    {"CHARLIE", 114},   {"CHARLOTTE", 115}, {"CHASE", 116},
    {"CHLOE", 117},     {"CHRISTIAN", 118}, {"CHRISTOPHER", 119},
    {"CLAIRE", 120},    {"CLARA", 121},     {"CLAYTON", 122},
    {"COLE", 123},      {"COLIN", 124},     {"COLTON", 125},
    {"CONNOR", 126},    {"COOPER", 127},    {"CORA", 128},
    {"DAISY", 129},     {"DAKOTA", 130},    {"DALEYZA", 131},
    {"DAMIAN", 132},    {"DANIEL", 133},    {"DANIELA", 134},
    {"DAVID", 135},     {"DAWSON", 136},    {"DEAN", 137},
    {"DECLAN", 138},    {"DELANEY", 139},   {"DELILAH", 140},
    {"DEREK", 141},     {"DESTINY", 142},   {"DIANA", 143},
    {"DIEGO", 144},     {"DOMINIC", 145},   {"DYLAN", 146},
    {"EASTON", 147},    {"EDEN", 148},      {"EDWARD", 149},
    {"ELEANOR", 150},   {"ELENA", 151},     {"ELI", 152},
    {"ELIANA", 153},    {"ELIAS", 154},     {"ELIJAH", 155},
    {"ELISE", 156},     {"ELIZA", 157},     {"ELIZABETH", 158},
    {"ELLA", 159},      {"ELLIANA", 160},   {"ELLIE", 161},
    {"ELLIOT", 162},    {"ELLIOTT", 163},   {"ELOISE", 164},
    {"EMERSON", 165},   {"EMERSYN", 166},   {"EMERY", 167},
    {"EMILIA", 168},    {"EMILIANO", 169},  {"EMILY", 170},
    {"EMMA", 171},      {"EMMANUEL", 172},  {"EMMETT", 173},
    {"ERIC", 174},      {"ESTHER", 175},    {"ETHAN", 176},
    {"EVA", 177},       {"EVAN", 178},      {"EVELYN", 179},
    {"EVERETT", 180},   {"EVERLY", 181},    {"EZEKIEL", 182},
    {"EZRA", 183},      {"FAITH", 184},     {"FELIX", 185},
    {"FINLEY", 186},    {"FINN", 187},      {"FIONA", 188},
    {"GABRIEL", 189},   {"GABRIELLA", 190}, {"GAEL", 191},
    {"GAVIN", 192},     {"GENESIS", 193},   {"GENEVIEVE", 194},
    {"GEORGE", 195},    {"GEORGIA", 196},   {"GIANNA", 197},
    {"GIOVANNI", 198},  {"GRACE", 199},     {"GRACIE", 200},
    {"GRAHAM", 201},    {"GRANT", 202},     {"GRAYSON", 203},
    {"GREYSON", 204},   {"GRIFFIN", 205},   {"HADLEY", 206},
    {"HAILEY", 207},    {"HANNAH", 208},    {"HARLEY", 209},
    {"HARMONY", 210},   {"HARPER", 211},    {"HARRISON", 212},
    {"HAYDEN", 213},    {"HAZEL", 214},     {"HENRY", 215},
    {"HOLDEN", 216},    {"HUDSON", 217},    {"HUNTER", 218},
    {"IAN", 219},       {"IRIS", 220},      {"ISAAC", 221},
    {"ISABEL", 222},    {"ISABELLA", 223},  {"ISABELLE", 224},
    {"ISAIAH", 225},    {"ISLA", 226},      {"ISRAEL", 227},
    {"IVAN", 228},      {"IVY", 229},       {"JACE", 230},
    {"JACK", 231},      {"JACKSON", 232},   {"JACOB", 233},
    {"JADE", 234},      {"JADEN", 235},     {"JAKE", 236},
    {"JAMES", 237},     {"JAMESON", 238},   {"JASMINE", 239},
    {"JASON", 240},     {"JASPER", 241},    {"JAVIER", 242},
    {"JAX", 243},       {"JAXON", 244},     {"JAXSON", 245},
    {"JAYCE", 246},     {"JAYDEN", 247},    {"JAYLA", 248},
    {"JEREMIAH", 249},  {"JEREMY", 250},    {"JESSE", 251},
    {"JESSICA", 252},   {"JESUS", 253},     {"JOANNA", 254},
    {"JOCELYN", 255},   {"JOEL", 256},      {"JOHN", 257},
    {"JONAH", 258},     {"JONATHAN", 259},  {"JORDAN", 260},
    {"JORDYN", 261},    {"JORGE", 262},     {"JOSE", 263},
    {"JOSEPH", 264},    {"JOSEPHINE", 265}, {"JOSHUA", 266},
    {"JOSIAH", 267},    {"JOSIE", 268},     {"JOSUE", 269},
    {"JUAN", 270},      {"JUDAH", 271},     {"JUDE", 272},
    {"JULIA", 273},     {"JULIAN", 274},    {"JULIANA", 275},
    {"JULIANNA", 276},  {"JULIET", 277},    {"JULIETTE", 278},
    {"JUNE", 279},      {"JUSTIN", 280},    {"KADEN", 281},
    {"KAI", 282},       {"KAIDEN", 283},    {"KALEB", 284},
    {"KARTER", 285},    {"KATHERINE", 286}, {"KAYDEN", 287},
    {"KAYLA", 288},     {"KAYLEE", 289},    {"KENDALL", 290},
    {"KENNEDY", 291},   {"KENNETH", 292},   {"KEVIN", 293},
    {"KHLOE", 294},     {"KILLIAN", 295},   {"KIMBERLY", 296},
    {"KING", 297},      {"KINGSTON", 298},  {"KINSLEY", 299},
    {"KNOX", 300},      {"KYLE", 301},      {"KYLIE", 302},
    {"KYRIE", 303},     {"LAILA", 304},     {"LANDON", 305},
    {"LAUREN", 306},    {"LAYLA", 307},     {"LEAH", 308},
    {"LEILA", 309},     {"LEILANI", 310},   {"LEO", 311},
    {"LEON", 312},      {"LEONARDO", 313},  {"LEVI", 314},
    {"LIAM", 315},      {"LILA", 316},      {"LILIANA", 317},
    {"LILLIAN", 318},   {"LILLY", 319},     {"LILY", 320},
    {"LINCOLN", 321},   {"LOGAN", 322},     {"LOLA", 323},
    {"LONDON", 324},    {"LONDYN", 325},    {"LORENZO", 326},
    {"LUCA", 327},      {"LUCAS", 328},     {"LUCIA", 329},
    {"LUCY", 330},      {"LUIS", 331},      {"LUKAS", 332},
    {"LUKE", 333},      {"LUNA", 334},      {"LYDIA", 335},
    {"LYLA", 336},      {"MACKENZIE", 337}, {"MADDOX", 338},
    {"MADELINE", 339},  {"MADELYN", 340},   {"MADISON", 341},
    {"MAGGIE", 342},    {"MAKAYLA", 343},   {"MALACHI", 344},
    {"MALIA", 345},     {"MARCUS", 346},    {"MARGARET", 347},
    {"MARIA", 348},     {"MARIAH", 349},    {"MARK", 350},
    {"MARLEY", 351},    {"MARY", 352},      {"MASON", 353},
    {"MATEO", 354},     {"MATIAS", 355},    {"MATTEO", 356},
    {"MATTHEW", 357},   {"MAVERICK", 358},  {"MAX", 359},
    {"MAXIMUS", 360},   {"MAXWELL", 361},   {"MAYA", 362},
    {"MCKENZIE", 363},  {"MELANIE", 364},   {"MELODY", 365},
    {"MESSIAH", 366},   {"MIA", 367},       {"MICAH", 368},
    {"MICHAEL", 369},   {"MICHELLE", 370},  {"MIGUEL", 371},
    {"MILA", 372},      {"MILES", 373},     {"MILO", 374},
    {"MOLLY", 375},     {"MORGAN", 376},    {"MYA", 377},
    {"MYLES", 378},     {"NAOMI", 379},     {"NATALIA", 380},
    {"NATALIE", 381},   {"NATHAN", 382},    {"NATHANIEL", 383},
    {"NEVAEH", 384},    {"NICHOLAS", 385},  {"NICOLAS", 386},
    {"NICOLE", 387},    {"NOAH", 388},      {"NOELLE", 389},
    {"NOLAN", 390},     {"NORA", 391},      {"NORAH", 392},
    {"NOVA", 393},      {"OLIVER", 394},    {"OLIVIA", 395},
    {"OMAR", 396},      {"OSCAR", 397},     {"OWEN", 398},
    {"PAIGE", 399},     {"PAISLEY", 400},   {"PARKER", 401},
    {"PATRICK", 402},   {"PAUL", 403},      {"PAXTON", 404},
    {"PAYTON", 405},    {"PENELOPE", 406},  {"PETER", 407},
    {"PEYTON", 408},    {"PIPER", 409},     {"PRESLEY", 410},
    {"PRESTON", 411},   {"QUINN", 412},     {"RACHEL", 413},
    {"RAELYNN", 414},   {"REAGAN", 415},    {"REBECCA", 416},
    {"REESE", 417},     {"REMI", 418},      {"REMINGTON", 419},
    {"RHETT", 420},     {"RICHARD", 421},   {"RILEY", 422},
    {"RIVER", 423},     {"ROBERT", 424},    {"ROMAN", 425},
    {"ROSALIE", 426},   {"ROSE", 427},      {"ROWAN", 428},
    {"RUBY", 429},      {"RYAN", 430},      {"RYDER", 431},
    {"RYKER", 432},     {"RYLEE", 433},     {"RYLEIGH", 434},
    {"SADIE", 435},     {"SAMANTHA", 436},  {"SAMUEL", 437},
    {"SANTIAGO", 438},  {"SARA", 439},      {"SARAH", 440},
    {"SAVANNAH", 441},  {"SAWYER", 442},    {"SCARLETT", 443},
    {"SEBASTIAN", 444}, {"SELENA", 445},    {"SERENITY", 446},
    {"SIENNA", 447},    {"SILAS", 448},     {"SKYLAR", 449},
    {"SLOANE", 450},    {"SOFIA", 451},     {"SOPHIA", 452},
    {"SOPHIE", 453},    {"STELLA", 454},    {"STEVEN", 455},
    {"SUMMER", 456},    {"SYDNEY", 457},    {"TAYLOR", 458},
    {"TEAGAN", 459},    {"TESSA", 460},     {"THEODORE", 461},
    {"THIAGO", 462},    {"THOMAS", 463},    {"TIMOTHY", 464},
    {"TRINITY", 465},   {"TRISTAN", 466},   {"TUCKER", 467},
    {"TYLER", 468},     {"VALENTINA", 469}, {"VALERIA", 470},
    {"VALERIE", 471},   {"VANESSA", 472},   {"VICTOR", 473},
    {"VICTORIA", 474},  {"VINCENT", 475},   {"VIOLET", 476},
    {"VIVIAN", 477},    {"WAYLON", 478},    {"WESLEY", 479},
    {"WESTON", 480},    {"WILLIAM", 481},   {"WILLOW", 482},
    {"WYATT", 483},     {"XANDER", 484},    {"XAVIER", 485},
    {"XIMENA", 486},    {"ZACHARY", 487},   {"ZANDER", 488},
    {"ZANE", 489},      {"ZAYDEN", 490},    {"ZION", 491},
    {"ZOE", 492},       {"ZOEY", 493}};

unsigned long long power10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 100000000};

struct myData {
  Data *d;
  unsigned int firstNameOrder;
  unsigned int lastNameOrder;
  unsigned long long ssnOrder;
};

bool compareFirstName(myData *first, myData *last) {
  return first->firstNameOrder < last->firstNameOrder;
}

bool compareLastName(myData *first, myData *last) {
  return first->lastNameOrder < last->lastNameOrder;
}

bool compareSSN(myData *first, myData *last) {
  return first->ssnOrder < last->ssnOrder;
}

bool compare(myData *first, myData *last) {
  if (first->lastNameOrder != first->lastNameOrder) {
    return first->lastNameOrder < last->lastNameOrder;
  }
  if (first->firstNameOrder != first->firstNameOrder) {
    return first->firstNameOrder < last->firstNameOrder;
  }
  return first->ssnOrder < last->ssnOrder;
}

const unsigned int AFS_RADIX = 32;
const unsigned int AFS_RADIX_POWER = 5;
const int STDSORT_CUTOFF = 50;

enum field {
  lastName = 1,
  firstName = 2,
  ssn = 3,
};

struct nameLengths {
  int firstName = 0;
  int lastName = 0;
};

unsigned long long valueAt(myData *d, int pos, field type) {
  unsigned int shift = pos * AFS_RADIX_POWER;
  if (type == field::firstName) {
    return (d->firstNameOrder >> shift) % AFS_RADIX;
  }
  if (type == field::lastName) {
    return (d->lastNameOrder >> shift) % AFS_RADIX;
  }
  return (d->ssnOrder >> shift) % AFS_RADIX;
}

void _afsSwapAll(myData **&v, int *offsets, int start, int digit, field type) {
  int i = start;
  int nf[AFS_RADIX] = {};
  int current_block = 0;
  copy(offsets, offsets + AFS_RADIX, begin(nf));
  while (current_block < AFS_RADIX - 1) {
    if (i >= start + offsets[current_block + 1]) {
      current_block += 1;
      continue;
    }
    int val = valueAt(v[i], digit, type);
    if (val == current_block) {
      i += 1;
      continue;
    }
    auto swap_to = start + nf[val];
    auto tmp = v[swap_to];
    v[swap_to] = v[i];
    v[i] = tmp;
    nf[val] += 1;
  }
}

void _afsOffsets(myData **&v, int start, int end, int digit, int *offsets,
                 field type) {
  int counts[AFS_RADIX] = {};
  for (int i = start; i < end; i++) {
    counts[valueAt(v[i], digit, type)] += 1;
  }
  int sum = 0;
  for (int i = 0; i < AFS_RADIX; i++) {
    offsets[i] = sum;
    sum += counts[i];
  }
}

void _recurseAmericanFlagSort(myData **&v, int start, int end, int digit,
                              int max, field type) {
  if (start + 1 >= end) {
    return;
  }
  if (end - start < STDSORT_CUTOFF) {
    if (start + 1 >= end) {
      return;
    }
    auto b = v + start;
    auto l = v + end;
    if (type == field::lastName) {
      sort(b, l, compareLastName);
    } else if (type == field::firstName) {
      sort(b, l, compareFirstName);
    } else {
      sort(b, l, compareSSN);
    }
    return;
  }
  int offsets[AFS_RADIX + 1] = {};
  offsets[AFS_RADIX] = end - start;
  _afsOffsets(v, start, end, digit, offsets, type);
  _afsSwapAll(v, offsets, start, digit, type);
  if (digit == 0) {
    return;
  }
  for (int i = 0; i < AFS_RADIX; i++) {
    _recurseAmericanFlagSort(v, start + offsets[i], start + offsets[i + 1],
                             digit - 1, max, type);
  }
}

int max_digit(field type) {
  if (type == field::ssn) {
    return 5;
  }
  return 2;
}

void americanFlagSort(myData **v, int start, int end, field type) {
  int md = max_digit(type);
  _recurseAmericanFlagSort(v, start, end, md, md, type);
}

myData *vec[1200000];

void sortDataList(list<Data *> &l) {
  // Fill this in
  int dataSize = l.size();

  // American Flag Sort try
  int i = 0;
  for (auto it = l.begin(); it != l.end(); it++) {
    auto a = *it;
    const char *ssn = a->ssn.c_str();
    vec[i++] = new myData{
        a,
        firstNamesOrdered[a->firstName],
        lastNamesOrdered[a->lastName],
        power10[8] * (ssn[0] - '0') + power10[7] * (ssn[1] - '0') +
            power10[6] * (ssn[2] - '0') + power10[5] * (ssn[4] - '0') +
            power10[4] * (ssn[5] - '0') + power10[3] * (ssn[7] - '0') +
            power10[2] * (ssn[8] - '0') + power10[1] * (ssn[9] - '0') +
            (ssn[10] - '0'),
    };
  }

  americanFlagSort(vec, 0, dataSize, field::lastName);
  list<int> offsetsLists = {0};
  for (int i = 1; i < dataSize; i++) {
    if (vec[i]->lastNameOrder == vec[i - 1]->lastNameOrder) {
      continue;
    }
    offsetsLists.push_back(i);
  }
  offsetsLists.push_back(dataSize);

  for (auto it = next(offsetsLists.begin()); it != offsetsLists.end(); it++) {
    auto p = prev(it);
    americanFlagSort(vec, *p, *it, field::firstName);
  }

  list<int> offsetsLists1 = {0};
  for (int i = 1; i < dataSize; i++) {
    if (vec[i]->firstNameOrder == vec[i - 1]->firstNameOrder &&
        vec[i]->lastNameOrder == vec[i - 1]->lastNameOrder) {
      continue;
    }
    offsetsLists1.push_back(i);
  }
  offsetsLists1.push_back(dataSize);

  for (auto it = next(offsetsLists1.begin()); it != offsetsLists1.end(); it++) {
    americanFlagSort(vec, *prev(it), *it, field::ssn);
  }

  l.clear();
  for (int i = 0; i < dataSize; i++) l.push_back(vec[i]->d);
}

