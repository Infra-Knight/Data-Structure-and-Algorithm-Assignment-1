/*
* =========================================================================================
* Name        : processData.cpp
* Description : student code for Assignment 1 - Data structures and Algorithms - Spring 2018
* =========================================================================================
*/
#include "requestLib.h"
#include "dbLib.h"


/// Initialize and Finalize any global data that you use in the program

struct infoRecord {
	char _ID[16];
	int A[50];
	int B[50];
	int k, b, b1, tg, tg_MTV, tg_LPV, bool_CNS;
	size_t _size, _idx;
	double lat1, lon1, lat2, lon2, _lat, _lon, _dis_LPV, _dis_SPV, _dis_MVV, _dis_CNS, _dis_CAS, _evdis, x1, x2, y1, y2, qd, x, y, qdd;
	int dem, dem1, dem2;
	bool _exist;
	time_t _longest, t1, t2, t;
	L1Item <size_t> *arr;
	L1List<char *> _idList;
	L1List<VRecord> pNode;
	infoRecord() {
		strcpy(_ID, "");
		A[0] = 0;
		B[0] = 0;
		k = 0; b = 0; b1 = 0, tg = 0, tg_MTV = 0, tg_LPV=0, bool_CNS=0;
		_size = 0;
		_dis_LPV = 0; _dis_SPV = 0; _dis_MVV = 0; _dis_CNS = 0; _dis_CAS = 0; lat1 = 0; lon1 = 0; lat2 = 0; lon2 = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, qd = 0, x = 0, y = 0, qdd = 0;
		dem = 0, dem1 = 0, dem2 = 0;
		_lat = 0;
		_lon = 0;
		_exist = 0;
		_idx = 0;
		t1 = 0; t2 = 0, t = 0;
		_longest = 0;
		_evdis = 0;
	};
	infoRecord(const char *s) {
		strcpy(_ID, s);
		A[0] = 0;
		B[0] = 0;
		k = 0; b = 0; b1 = 0, tg = 0, tg_MTV = 0, tg_LPV = 0, bool_CNS = 0;
		_size = 0;
		_dis_LPV = 0; _dis_SPV = 0; _dis_MVV = 0; _dis_CNS = 0; _dis_CAS = 0; lat1 = 0; lon1 = 0; lat2 = 0; lon2 = 0, x2 = 0, y1 = 0, y2 = 0, qd = 0, x = 0, y = 0, qdd = 0;
		dem = 0, dem1 = 0; dem2 = 0;
		_lat = 0;
		_lon = 0;
		_exist = 0;
		_idx = 0;
		t1 = 0; t2 = 0, t = 0;
		_longest = 0;
		_evdis = 0;
	}
};



L1List<char *>idList;
//L1List<char *>longestTimeStillList;
//L1List<VRecord> dbList;
void cmpID(char *&id, void* res) {
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id, temp->_ID) == 0)
	{
		temp->_exist = 1;
	}
}
bool findID(char *s, L1List<char*> idList) {
	infoRecord *des = new infoRecord(s);
	idList.traverse(&cmpID, des);
	return des->_exist;
}
void buIDList(VRecord &node, void* add) {
	L1List<char*>* b = (L1List<char*>*) add;
	if (!findID(node.id, *b)) {
		char *temp = node.id;
		(*b).insertHead(temp);
	}
	return;
}
void code_0(L1List<VRecord> bList, L1List<char*> &idList) {
	bList.traverse(&buIDList, &idList);
}



double placeHolderXMST = 0;
double placeHolderYMST = 0;
char placeHolderIDMST[16];
//char temp_placeHolderIDMST[16];
double distance_error_MST = 0;
int placeHolder_timestamp_MST = 0;
int finalTime_MST = 0;
void MSTcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		/*cout << id.x << endl;
		cout << id.y << endl;
		cout << "0" << endl;*/
		//cout << id.id << endl;
		//cout << placeHolderIDMST<<" uhmmm" << endl;


		//co cong don
		if (strcmp(id.id, placeHolderIDMST) == 0) {
			//cout << "same" << endl;
			distance_error_MST = distance_error_MST + distanceVR(placeHolderYMST, placeHolderXMST, id.y, id.x);
			if (distance_error_MST < 0.005) {
				temp->tg = temp->tg + (id.timestamp - placeHolder_timestamp_MST);
			}

			else if (distance_error_MST >= 0.005) {
				distance_error_MST = 0;
			}
			/*for (int i = 0; i < 16; i++) {
			temp_placeHolderIDMST[i] = id.id[i];
			}*/
		}
		else {
			//cout << "dif" << endl;
			distance_error_MST = 0;

		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDMST[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		placeHolder_timestamp_MST = id.timestamp;
		placeHolderXMST = id.x;
		placeHolderYMST = id.y;
	}
}
double findIDrecList(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&MSTcmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->tg;
}
void calculate_MST(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	int a = findIDrecList(node, *b);
	if (a > finalTime_MST) {
		finalTime_MST = a;
		/*for (int i = 0; i < 16; i++) {
		temp_placeHolderIDMST[i] = placeHolderIDMST[i];
		}*/
	}
}
void code_MST(L1List<VRecord> &bList) {
	idList.traverse(&calculate_MST, &bList);
	cout << "MST: " << finalTime_MST << "s" << endl;
	//cout << temp_placeHolderIDMST << endl;
	placeHolderXMST = 0;
	placeHolderYMST = 0;
	placeHolderIDMST[16];
	//char temp_placeHolderIDMST[16];
	distance_error_MST = 0;
	placeHolder_timestamp_MST = 0;
	finalTime_MST = 0;
}



int demMRV = 0;
int demMRV1 = 0;
int maxMRV = 0;
void MRVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		temp->dem = temp->dem + 1;
	}
}
int MRVFindID(char* s, L1List<VRecord> bList)
{
	infoRecord *des = new infoRecord(s);
	bList.traverse(&MRVcmpID, des);
	return des->dem;
}
void MRVbuIDList(char* &node, void* add)
{
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	int a = MRVFindID(node, *b);
	if (a >= maxMRV)
	{
		maxMRV = a;
		demMRV = demMRV1;
	}
	demMRV1 = demMRV1 + 1;
}
void code_MRV(L1List<VRecord> &bList)
{
	idList.traverse(&MRVbuIDList, &bList);
	cout << "MRV: " << idList.at(demMRV) << endl;
	demMRV = 0;
	demMRV1 = 0;
	maxMRV = 0;
}



int demLRV = 0;
int demLRV1 = 0;
int minLRV = 10000;
void LRVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		temp->dem = temp->dem + 1;
	}
}
int LRVFindID(char* s, L1List<VRecord> bList)
{
	infoRecord *des = new infoRecord(s);
	bList.traverse(&LRVcmpID, des);
	return des->dem;
}
void LRVbuIDList(char* &node, void* add)
{
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	int a = LRVFindID(node, *b);
	if (a <= minLRV)
	{
		minLRV = a;
		demLRV = demLRV1;
	}
	demLRV1 = demLRV1 + 1;
}
void code_LRV(L1List<VRecord> &bList)
{
	idList.traverse(&LRVbuIDList, &bList);
	cout << "LRV: " << idList.at(demLRV) << endl;
	demLRV = 0;
	demLRV1 = 0;
	minLRV = 10000;
}



double placeHolderXMTV = 0;
double placeHolderYMTV = 0;
char placeHolderIDMTV[16];
char temp_placeHolderIDMTV[16];
char final_placeHolderIDMTV[16];
double distance_error_MTV = 0;
int placeHolder_timestamp_MTV = 0;
int finalTime_MTV = 0;
void MTVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		/*cout << id.x << endl;
		cout << id.y << endl;
		cout << "0" << endl;*/
		//cout << id.id << endl;
		//cout << placeHolderIDMST<<" uhmmm" << endl;


		//co cong don
		if (strcmp(id.id, placeHolderIDMTV) == 0) {
			//cout << "same" << endl;
			distance_error_MTV = distance_error_MTV + distanceVR(placeHolderYMTV, placeHolderXMTV, id.y, id.x);
			if (distance_error_MTV >= 0.005) {
				temp->tg_MTV = temp->tg_MTV + (id.timestamp - placeHolder_timestamp_MTV);
				distance_error_MTV = 0;
			}

			else if (distance_error_MTV < 0.005) {
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDMTV[i] = id.id[i];
			}
		}
		else {
			//cout << "dif" << endl;
			distance_error_MTV = 0;

		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDMTV[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		placeHolder_timestamp_MTV = id.timestamp;
		placeHolderXMTV = id.x;
		placeHolderYMTV = id.y;
	}
}
double findIDrecList_MTV(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&MTVcmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->tg_MTV;
}
void calculate_MTV(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	int a = findIDrecList_MTV(node, *b);
	//cout << "titanium " << a << endl;
	if (a > finalTime_MTV) {
		finalTime_MTV = a;
		for (int i = 0; i < 16; i++) {
			final_placeHolderIDMTV[i] = temp_placeHolderIDMTV[i];
		}
	}
}
void code_MTV(L1List<VRecord> &bList) {
	idList.traverse(&calculate_MTV, &bList);
	cout << "MTV: " << final_placeHolderIDMTV << endl;
	//cout << final_placeHolderIDMTV << endl;
	placeHolderXMTV = 0;
	placeHolderYMTV = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDMTV[i]='0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDMTV[i]='0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDMTV[i]='0';
	}
	distance_error_MTV = 0;
	placeHolder_timestamp_MTV = 0;
	finalTime_MTV = 0;
}



double placeHolderXLPV = 0;
double placeHolderYLPV = 0;
char placeHolderIDLPV[16];
char temp_placeHolderIDLPV[16];
char final_placeHolderIDLPV[16];
double distance_error_LPV = 0;
//int placeHolder_timestamp_LPV = 0;
double finalDis_LPV = 0;
void LPVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		/*cout << id.x << endl;
		cout << id.y << endl;
		cout << "0" << endl;*/
		//cout << id.id << endl;
		//cout << placeHolderIDMST<<" uhmmm" << endl;


		//co cong don
		if (strcmp(id.id, placeHolderIDLPV) == 0) {
			//cout << "same" << endl;
			distance_error_LPV = distance_error_LPV + distanceVR(placeHolderYLPV, placeHolderXLPV, id.y, id.x);
			if (distance_error_LPV >= 0.005) {
				//temp->tg_LPV = temp->tg_LPV + (id.timestamp - placeHolder_timestamp_LPV);
				temp->_dis_LPV= temp->_dis_LPV+ distanceVR(placeHolderYLPV, placeHolderXLPV, id.y, id.x);
				distance_error_LPV = 0;
			}

			else if (distance_error_LPV < 0.005) {
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDLPV[i] = id.id[i];
			}
		}
		else {
			//cout << "dif" << endl;
			distance_error_LPV = 0;

		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDLPV[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		//placeHolder_timestamp_LPV = id.timestamp;
		placeHolderXLPV = id.x;
		placeHolderYLPV = id.y;
	}
}
double findIDrecList_LPV(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&LPVcmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->_dis_LPV;
}
void calculate_LPV(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	double a = findIDrecList_LPV(node, *b);
	//cout << "titanium " << a << endl;
	if (a > finalDis_LPV) {
		finalDis_LPV = a;
		for (int i = 0; i < 16; i++) {
			final_placeHolderIDLPV[i] = temp_placeHolderIDLPV[i];
		}
	}
}
void code_LPV(L1List<VRecord> &bList) {
	idList.traverse(&calculate_LPV, &bList);
	cout << "LPV: " << final_placeHolderIDLPV << endl;
	//cout << final_placeHolderIDMTV << endl;
	placeHolderXLPV = 0;
	placeHolderYLPV = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDLPV[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDLPV[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDLPV[i] = '0';
	}
	distance_error_LPV = 0;
	//placeHolder_timestamp_LPV = 0;
	finalDis_LPV = 0;
}



double placeHolderXSPV = 0;
double placeHolderYSPV = 0;
char placeHolderIDSPV[16];
char temp_placeHolderIDSPV[16];
char final_placeHolderIDSPV[16];
double distance_error_SPV = 0;
//int placeHolder_timestamp_LPV = 0;
double finalDis_SPV = 10000;
void SPVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		/*cout << id.x << endl;
		cout << id.y << endl;
		cout << "0" << endl;*/
		//cout << id.id << endl;
		//cout << placeHolderIDMST<<" uhmmm" << endl;


		//co cong don
		if (strcmp(id.id, placeHolderIDSPV) == 0) {
			//cout << "same" << endl;
			distance_error_SPV = distance_error_SPV + distanceVR(placeHolderYSPV, placeHolderXSPV, id.y, id.x);
			if (distance_error_SPV >= 0.005) {
				//temp->tg_LPV = temp->tg_LPV + (id.timestamp - placeHolder_timestamp_LPV);
				temp->_dis_SPV = temp->_dis_SPV + distanceVR(placeHolderYSPV, placeHolderXSPV, id.y, id.x);
				distance_error_SPV = 0;
			}

			else if (distance_error_SPV < 0.005) {
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDSPV[i] = id.id[i];
				//cout << temp_placeHolderIDSPV << endl;
			}
		}
		else {
			//cout << "dif" << endl;
			distance_error_SPV = 0;

		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDSPV[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		//placeHolder_timestamp_LPV = id.timestamp;
		placeHolderXSPV = id.x;
		placeHolderYSPV = id.y;
	}
}
double findIDrecList_SPV(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&SPVcmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->_dis_SPV;
}
void calculate_SPV(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	double a = findIDrecList_SPV(node, *b);
	//cout << "titanium " << a << endl;
	if (a <= finalDis_SPV) {
		finalDis_SPV = a;
		//cout << temp_placeHolderIDSPV << endl;
		for (int i = 0; i < 16; i++) {
			
			final_placeHolderIDSPV[i] = temp_placeHolderIDSPV[i];
			//cout << final_placeHolderIDSPV << endl;
		}

	}
}
void code_SPV(L1List<VRecord> &bList) {
	idList.traverse(&calculate_SPV, &bList);
	cout << "SPV: " << final_placeHolderIDSPV << endl;
	//cout << final_placeHolderIDMTV << endl;
	placeHolderXSPV = 0;
	placeHolderYSPV = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDSPV[i] ='0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDSPV[i]='0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDSPV[i]='0';
	}
	distance_error_SPV = 0;
	//placeHolder_timestamp_LPV = 0;
	finalDis_SPV = 0;
}



double placeHolderXMVV = 0;
double placeHolderYMVV = 0;
char placeHolderIDMVV[16];
char temp_placeHolderIDMVV[16];
char final_placeHolderIDMVV[16];
double distance_error_MVV = 0;
int count_MVV = 0;
//int placeHolder_timestamp_LPV = 0;
double finalDis_MVV = 0;
void MVVcmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		//co cong don
		if (strcmp(id.id, placeHolderIDMVV) == 0) {
			//cout << "same" << endl;
			distance_error_MVV = distance_error_MVV + distanceVR(placeHolderYMVV, placeHolderXMVV, id.y, id.x);
			if (distance_error_MVV >= 0.005) {
				//temp->tg_LPV = temp->tg_LPV + (id.timestamp - placeHolder_timestamp_LPV);
				temp->_dis_MVV = temp->_dis_MVV + distanceVR(placeHolderYMVV, placeHolderXMVV, id.y, id.x);
				distance_error_MVV = 0;
				count_MVV++;
			}

			else if (distance_error_MVV < 0.005) {
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDMVV[i] = id.id[i];
			}
		}
		else {
			//cout << "dif" << endl;
			distance_error_MVV = 0;
			count_MVV = 0;
		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDMVV[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		//placeHolder_timestamp_LPV = id.timestamp;
		placeHolderXMVV = id.x;
		placeHolderYMVV = id.y;
	}
}
double findIDrecList_MVV(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&MVVcmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->_dis_MVV;
}
void calculate_MVV(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	double a = findIDrecList_MVV(node, *b);
	//cout << a <<" "<<count_MVV << endl;
	a = a / count_MVV;
	//cout << "titanium " << a << endl;
	if (a > finalDis_MVV) {
		finalDis_MVV = a;
		for (int i = 0; i < 16; i++) {
			final_placeHolderIDMVV[i] = temp_placeHolderIDMVV[i];
		}
	}
}
void code_MVV(L1List<VRecord> &bList) {
	idList.traverse(&calculate_MVV, &bList);
	cout << "MVV: " << final_placeHolderIDMVV << endl;
	//cout << final_placeHolderIDMTV << endl;
	placeHolderXMVV = 0;
	placeHolderYMVV = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDMVV[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDMVV[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDMVV[i] = '0';
	}
	distance_error_MVV = 0;
	//placeHolder_timestamp_LPV = 0;
	finalDis_MVV = 0;
}



double placeHolderXCNS = 0;
double placeHolderYCNS = 0;
char placeHolderIDCNS[16];
char temp_placeHolderIDCNS[16];
char final_placeHolderIDCNS[16];
double distance_error_CNS = 0;
int count_CNS = 0;
//int placeHolder_timestamp_LPV = 0;
double finalDis_CNS = 0;
double b_dis_CNS = 0;
int bool_move_const1_CNS = 0;
int bool_move_const2_CNS = 0;
int final_count_CNS = 0;
int something = 0;
bool move_and_stop = false;
int w = 0;
void CNScmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		/*w = 1;
		something = 0;*/
		//co cong don
		if (strcmp(id.id, placeHolderIDCNS) == 0) {
			//something = 1;
			distance_error_CNS = distance_error_CNS + distanceVR(placeHolderYCNS, placeHolderXCNS, id.y, id.x);
			if (distance_error_CNS >= 0.005) {
				//temp->b1++;
			}

			else if (distance_error_CNS < 0.005) {
				//move_and_stop = true;
				temp->b1 = 1;
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDCNS[i] = id.id[i];
			}
		}
		else {
			distance_error_CNS = 0;
		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDCNS[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		//placeHolder_timestamp_LPV = id.timestamp;
		placeHolderXCNS = id.x;
		placeHolderYCNS = id.y;
		//cout << temp->_ID << " " << id.id << " " << temp->b1 << endl;
	}
}
double findIDrecList_CNS(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&CNScmpID, des);
	
	return des->b1;
}
void calculate_CNS(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	int a = findIDrecList_CNS(node, *b);
	/*if (something == 1 && move_and_stop == true) {
		final_count_CNS = final_count_CNS + a+w;
	}
	move_and_stop = false;
	w = 0;*/
	//cout << a << endl;
	if (a == 0) { final_count_CNS++; }
	//cout << final_count_CNS << endl;
}
void code_CNS(L1List<VRecord> &bList) {
	idList.traverse(&calculate_CNS, &bList);
	cout << "CNS: " << final_count_CNS<< endl;
	placeHolderXCNS = 0;
	placeHolderYCNS = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDCNS[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDCNS[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDCNS[i] = '0';
	}
	distance_error_CNS = 0;
	//placeHolder_timestamp_LPV = 0;
	finalDis_CNS = 0;
}



double placeHolderXCAS = 0;
double placeHolderYCAS = 0;
char placeHolderIDCAS[16];
char temp_placeHolderIDCAS[16];
char final_placeHolderIDCAS[16];
double distance_error_CAS = 0;
int count_CAS = 0;
//int placeHolder_timestamp_LPV = 0;
double finalDis_CAS = 0;
double b_dis_CAS = 0;
void CAScmpID(VRecord &id, void* res)
{
	infoRecord *temp = (infoRecord*)res;
	if (strcmp(id.id, temp->_ID) == 0)
	{
		//co cong don
		if (strcmp(id.id, placeHolderIDCAS) == 0) {
			//cout << "same" << endl;
			distance_error_CAS = distance_error_CAS + distanceVR(placeHolderYCAS, placeHolderXCAS, id.y, id.x);
			if (distance_error_CAS >= 0.005) {
				//temp->tg_LPV = temp->tg_LPV + (id.timestamp - placeHolder_timestamp_LPV);
				temp->_dis_CAS = temp->_dis_CAS + distanceVR(placeHolderYCAS, placeHolderXCAS, id.y, id.x)*1000;
				distance_error_CAS = 0;
				count_CAS++;
				
			}

			else if (distance_error_CAS < 0.005) {

				temp->_dis_CAS = temp->_dis_CAS + distanceVR(placeHolderYCAS, placeHolderXCAS, id.y, id.x)*1000;
				//distance_error_CNS = 0;
				count_CAS++;
			}
			for (int i = 0; i < 16; i++) {
				temp_placeHolderIDCAS[i] = id.id[i];
			}
		}
		else {
			//cout << "dif" << endl;
			distance_error_CAS = 0;
			//count_CNS = 0;
		}
		//cout << id.timestamp << endl;
		for (int i = 0; i < 16; i++) {
			placeHolderIDCAS[i] = id.id[i];
		}
		//cout << placeHolderIDMST << endl;
		//placeHolder_timestamp_LPV = id.timestamp;
		placeHolderXCAS = id.x;
		placeHolderYCAS = id.y;
	}
}
double findIDrecList_CAS(char *s, L1List<VRecord> bList) {
	infoRecord *des = new infoRecord(s);
	bList.traverse(&CAScmpID, des);
	//cout << des->x << endl;
	//cout << "1: " << des->tg << endl;
	return des->_dis_CAS;
}
void calculate_CAS(char* &node, void* add) {
	L1List<VRecord>* b = (L1List<VRecord>*) add;
	double a = findIDrecList_CAS(node, *b);
	//cout << a << endl;
	b_dis_CAS = b_dis_CAS+ a;
	//cout << a <<" "<<count_MVV << endl;
	/*if (count_CNS != 0) {
		a = a / count_CNS;
	}*/
	//cout << "titanium " << a << endl;
	/*if (b_dis_CNS > 0&&a>0) {
		b_dis_CNS = (b_dis_CNS + a) / 2;
	}
	else if (b_dis_CNS == 0) { b_dis_CNS = a; }*/
	//cout << "b: " << b_dis_CNS << endl;
}
void code_CAS(L1List<VRecord> &bList) {
	idList.traverse(&calculate_CAS, &bList);
	//cout << b_dis_CAS << endl;
	//cout << count_CAS << endl;
	cout << "CAS: " << (b_dis_CAS)/count_CAS <<" meter"<< endl;
	//cout << final_placeHolderIDMTV << endl;
	placeHolderXCAS = 0;
	placeHolderYCAS = 0;
	for (int i = 0; i < 16; i++) {
		placeHolderIDCAS[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		temp_placeHolderIDCAS[i] = '0';
	}
	for (int i = 0; i < 16; i++) {
		final_placeHolderIDCAS[i] = '0';
	}
	distance_error_CAS = 0;
	//placeHolder_timestamp_LPV = 0;
	finalDis_CAS = 0;
}



bool isEqual(const char x[], const  char y[])
{
	if (x[0] == y[0] && x[1] == y[1] && x[2] == y[2]) {
		return true;
	}
	else return false;
}

int numberOfDevice(L1List<VRecord>& recList) {
	L1List<VRecord> myList;
	L1List<VRecord> myList51B04;
	L1List<VRecord> myList51B06;
	L1List<VRecord> myList51B0;
	L1List<VRecord> myList51B14;
	L1List<VRecord> myList51B1;
	L1List<VRecord> myList51B;
	L1List<VRecord> myList51C;
	L1List<VRecord> myList53N3;
	L1List<VRecord> myList53N4;
	L1List<VRecord> myList53N;
	bool same;
	for (int n = 0; n < recList.getSize(); n++) {
		same = false;
		if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
			for (int z = 0; z <myList51B04.getSize(); z++) {
				if (recList[n].id[5] == myList51B04[z].id[5] && recList[n].id[6] == myList51B04[z].id[6] && recList[n].id[7] == myList51B04[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B04.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
			for (int z = 0; z <myList51B06.getSize(); z++) {
				if (recList[n].id[5] == myList51B06[z].id[5] && recList[n].id[6] == myList51B06[z].id[6] && recList[n].id[7] == myList51B06[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B06.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
			for (int z = 0; z <myList51B0.getSize(); z++) {
				if (recList[n].id[4] == myList51B0[z].id[4] && recList[n].id[5] == myList51B0[z].id[5] && recList[n].id[6] == myList51B0[z].id[6] && recList[n].id[7] == myList51B0[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B0.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
			for (int z = 0; z <myList51B14.getSize(); z++) {
				if (recList[n].id[5] == myList51B14[z].id[5] && recList[n].id[6] == myList51B14[z].id[6] && recList[n].id[7] == myList51B14[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B14.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
			for (int z = 0; z <myList51B1.getSize(); z++) {
				if (recList[n].id[4] == myList51B1[z].id[4] && recList[n].id[5] == myList51B1[z].id[5] && recList[n].id[6] == myList51B1[z].id[6] && recList[n].id[7] == myList51B1[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B1.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
			for (int z = 0; z <myList51B.getSize(); z++) {
				if (recList[n].id[3] == myList51B[z].id[3] && recList[n].id[4] == myList51B[z].id[4] && recList[n].id[5] == myList51B[z].id[5] && recList[n].id[6] == myList51B[z].id[6] && recList[n].id[7] == myList51B[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51B.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
			for (int z = 0; z < myList51C.getSize(); z++) {
				if (recList[n].id[3] == myList51C[z].id[3] && recList[n].id[4] == myList51C[z].id[4] && recList[n].id[5] == myList51C[z].id[5] && recList[n].id[6] == myList51C[z].id[6] && recList[n].id[7] == myList51C[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList51C.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
			for (int z = 0; z < myList53N3.getSize(); z++) {
				if (recList[n].id[4] == myList53N3[z].id[4] && recList[n].id[5] == myList53N3[z].id[5] && recList[n].id[6] == myList53N3[z].id[6] && recList[n].id[7] == myList53N3[z].id[7]) {
					same - true;
					break;
				}
			}
			if (same == false) {
				myList53N3.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
			for (int z = 0; z < myList53N4.getSize(); z++) {
				if (recList[n].id[4] == myList53N4[z].id[4] && recList[n].id[5] == myList53N4[z].id[5] && recList[n].id[6] == myList53N4[z].id[6] && recList[n].id[7] == myList53N4[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList53N4.push_back(recList[n]);
			}
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
			for (int z = 0; z < myList53N.getSize(); z++) {
				if (recList[n].id[3] == myList53N[z].id[3] && recList[n].id[4] == myList53N[z].id[4] && recList[n].id[5] == myList53N[z].id[5] && recList[n].id[6] == myList53N[z].id[6] && recList[n].id[7] == myList53N[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList53N.push_back(recList[n]);
			}
		}
		else {
			for (int z = 0; z < myList.getSize(); z++) {
				if (recList[n].id[0] == myList[z].id[0] && recList[n].id[1] == myList[z].id[1] && recList[n].id[2] == myList[z].id[2] && recList[n].id[3] == myList[z].id[3] && recList[n].id[4] == myList[z].id[4] &&
					recList[n].id[5] == myList[z].id[5] && recList[n].id[6] == myList[z].id[6] && recList[n].id[7] == myList[z].id[7]) {
					same = true;
					break;
				}
			}
			if (same == false) {
				myList.push_back(recList[n]);
			}
		}
	}
	int a = myList51B04.getSize() + myList51B06.getSize() + myList51B0.getSize() + myList51B14.getSize() + myList51B1.getSize() + myList51B.getSize() +
		myList51C.getSize() + myList53N3.getSize() + myList53N4.getSize() + myList53N.getSize() + myList.getSize();
	return a;
}

int findingMaxDistanceID(L1List<VRecord>& myList) {
	double distance = 0;
	int storedID = 0;
	for (int i = 0; i < myList.getSize(); i++) {
		int count = 0;
		double newdistance = 0;
		int placeHolderX = 0;
		for (int x = i; x < myList.getSize(); x++) {
			if (myList[i].id[0] == myList[x].id[0] && myList[i].id[1] == myList[x].id[1] && myList[i].id[2] == myList[x].id[2] && myList[i].id[3] == myList[x].id[3] && myList[i].id[4] == myList[x].id[4]
				&& myList[i].id[5] == myList[x].id[5] && myList[i].id[6] == myList[x].id[6] && myList[i].id[7] == myList[x].id[7]) {
				count++;
				if (count > 1) {
					newdistance = newdistance + distanceVR(myList[placeHolderX].x, myList[placeHolderX].y, myList[x].x, myList[x].y);
				}
				placeHolderX = x;
			}
		}
		if (newdistance > distance) {
			distance = newdistance;
			storedID = i;
		}
	}
	return storedID;
}

int findingMinDistanceID(L1List<VRecord>& myList) {
	double distance = 99999;
	int storedID = 0;
	for (int i = 0; i < myList.getSize(); i++) {
		int count = 0;
		double newdistance = 0;
		int placeHolderX = 0;
		for (int x = 0; x < myList.getSize(); x++) {
			if (myList[i].id[0] == myList[x].id[0] && myList[i].id[1] == myList[x].id[1] && myList[i].id[2] == myList[x].id[2] && myList[i].id[3] == myList[x].id[3] && myList[i].id[4] == myList[x].id[4]
				&& myList[i].id[5] == myList[x].id[5] && myList[i].id[6] == myList[x].id[6] && myList[i].id[7] == myList[x].id[7]) {
				count++;
				if (count > 1) {
					newdistance = newdistance + distanceVR(myList[placeHolderX].x, myList[placeHolderX].y, myList[x].x, myList[x].y);
				}
				placeHolderX = x;
			}
		}
		if (newdistance < distance && newdistance != 0) {
			distance = newdistance;
			storedID = i;
		}
	}
	return storedID;
}

float findingDistance(L1List<VRecord>& myList, int ID) {
	double distance = 0;
	int count = 0;
	int placeHolderX = 0;
	for (int i = 0; i < myList.getSize(); i++) {
		if (myList[i].id[0] == myList[ID].id[0] && myList[i].id[1] == myList[ID].id[1] && myList[i].id[2] == myList[ID].id[2] && myList[i].id[3] == myList[ID].id[3] && myList[i].id[4] == myList[ID].id[4] &&
			myList[i].id[5] == myList[ID].id[5] && myList[i].id[6] == myList[ID].id[6] && myList[i].id[7] == myList[ID].id[7]) {
			count++;
			if (count > 1) {
				distance = distance + distanceVR(myList[placeHolderX].x, myList[placeHolderX].y, myList[i].x, myList[i].y);
			}
			placeHolderX = i;
		}
	}
	return distance;
}

int findingNemo(L1List<VRecord>& myList) { //find max stop time, lol
	int finalTime = 0;
	if (myList.getSize() > 0) {
		if (myList.getSize() > 1) {
			for (int n = 0; n < myList.getSize(); n++) {
				int count = 0;
				int tempTime1 = 0;
				int storedID = 0;
				double placeHolderX = myList[0].x;
				double placeHolderY = myList[0].y;
				for (int i = n; i < myList.getSize(); i++) {
					if (myList[n].id[0] == myList[i].id[0] && myList[n].id[1] == myList[i].id[1] && myList[n].id[2] == myList[i].id[2] && myList[n].id[3] == myList[i].id[3] && myList[n].id[4] == myList[i].id[4]
						&& myList[n].id[5] == myList[i].id[5] && myList[n].id[6] == myList[i].id[6] && myList[n].id[7] == myList[i].id[7]) {
						count++;
						if (count > 1) {
							if (placeHolderX == myList[i].x && placeHolderY == myList[i].y) {
								tempTime1 = tempTime1 + (myList[i].timestamp - myList[storedID].timestamp);
							}
							else if (placeHolderX != myList[i].x || placeHolderY != myList[i].y) {
								if (tempTime1 > finalTime) { finalTime = tempTime1; }
							}
						}
						placeHolderX = myList[i].x;
						placeHolderY = myList[i].y;
						storedID = i;
					}
				}
			}
		}
		return finalTime;
	}
	else { return 0; }
}

int findingDory(L1List<VRecord>& myList) { //find total max move time
	int finalTime = 0;
	if (myList.getSize() > 0) {
		if (myList.getSize() > 1) {
			for (int n = 0; n < myList.getSize(); n++) {
				int count = 0;
				int tempTime1 = 0;
				int storedID = 0;
				double placeHolderX = myList[0].x;
				double placeHolderY = myList[0].y;
				for (int i = n; i < myList.getSize(); i++) {
					if (myList[n].id[0] == myList[i].id[0] && myList[n].id[1] == myList[i].id[1] && myList[n].id[2] == myList[i].id[2] && myList[n].id[3] == myList[i].id[3] && myList[n].id[4] == myList[i].id[4]
						&& myList[n].id[5] == myList[i].id[5] && myList[n].id[6] == myList[i].id[6] && myList[n].id[7] == myList[i].id[7]) {
						count++;
						if (count > 1) {
							if (placeHolderX != myList[i].x || placeHolderY != myList[i].y) {
								tempTime1 = tempTime1 + (myList[i].timestamp - myList[storedID].timestamp);
							}
							/*else if (placeHolderX == myList[i].x && placeHolderY == myList[i].y) {
							if (tempTime1 > finalTime) { finalTime = tempTime1; }
							}*/
						}
						placeHolderX = myList[i].x;
						placeHolderY = myList[i].y;
						storedID = i;
					}
				}
				if (tempTime1 > finalTime) { finalTime = tempTime1; }
			}
		}
		return finalTime;
	}
	else { return 0; }
}

int findingDoryID(L1List<VRecord>& myList) { //find total max move time
	int finalTime = 0;
	int finalID = 0;
	if (myList.getSize() > 0) {
		if (myList.getSize() > 1) {
			for (int n = 0; n < myList.getSize(); n++) {
				int count = 0;
				int tempTime1 = 0;
				int storedID = 0;
				double placeHolderX = myList[0].x;
				double placeHolderY = myList[0].y;
				for (int i = n; i < myList.getSize(); i++) {
					if (myList[n].id[0] == myList[i].id[0] && myList[n].id[1] == myList[i].id[1] && myList[n].id[2] == myList[i].id[2] && myList[n].id[3] == myList[i].id[3] && myList[n].id[4] == myList[i].id[4]
						&& myList[n].id[5] == myList[i].id[5] && myList[n].id[6] == myList[i].id[6] && myList[n].id[7] == myList[i].id[7]) {
						count++;
						if (count > 1) {
							if (placeHolderX != myList[i].x || placeHolderY != myList[i].y) {
								tempTime1 = tempTime1 + (myList[i].timestamp - myList[storedID].timestamp);
							}
							/*else if (placeHolderX == myList[i].x && placeHolderY == myList[i].y) {
							if (tempTime1 > finalTime) { finalTime = tempTime1; }
							}*/
						}
						placeHolderX = myList[i].x;
						placeHolderY = myList[i].y;
						storedID = i;
					}
				}
				if (tempTime1 > finalTime) { finalTime = tempTime1; finalID = storedID; }
			}
		}
		return finalID;
	}
	else { return 0; }
}

bool initVGlobalData(void** pGData) {
	// TODO: allocate global data if you think it is necessary.
	/// pGData contains the address of a pointer. You should allocate data for the global data
	/// and then assign its address to *pGData
	return true;
}
void releaseVGlobalData(void* pGData) {
	// TODO: release the data if you finish using it

}
int ff = 0;
bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
	// TODO: Your code comes here
	if (ff == 0)
	{
		code_0(recList, idList);
		//code_MST(recList);
		ff = 1;
	}
	if (isEqual(request.code, "CNV"))
	{
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		cout << "CNV: " << idList.getSize() << endl;
	}
	else if (isEqual(request.code, "VFF"))
	{
		if (recList.getSize() > 0) {
			cout << "VFF: " << recList[0].id << endl;
		}
		else { cout << "VFF: " << "empty!" << endl; }
	}
	else if (isEqual(request.code, "VFL"))
	{
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		if (recList.getSize() > 0) {
			cout << "VFL: " << idList.at(0) << endl;
		}
		else { cout << "VFL: " << "empty!" << endl; }
	}
	else if (isEqual(request.code, "VFY"))
	{
		if (recList.getSize() > 0) {
			for (int i = 0; i < recList.getSize(); i++) {
				if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
					&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
					cout << request.code << ": " << recList[i].y << endl;
					break;
				}

			}
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VFX"))
	{
		if (recList.getSize() > 0) {
			for (int i = 0; i < recList.getSize(); i++) {
				if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
					&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
					cout << request.code << ": " << recList[i].x << endl;
					break;
				}

			}
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VLY"))
	{
		if (recList.getSize() > 0) {
			for (int i = recList.getSize() - 1; i >= 0; i--) {
				if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
					&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
					cout << request.code << ": " << recList[i].y << endl;
					break;
				}
			}
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VLX"))
	{
		if (recList.getSize() > 0) {
			for (int i = recList.getSize() - 1; i >= 0; i--) {
				if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
					&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
					cout << request.code << ": " << recList[i].x << endl;
					break;
				}
			}
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VFT"))
	{
		int finalID;
		int count = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				count++;
				if (count == 1) {
					finalID = i;
				}
				if (count > 1) {
					if (recList[i].timestamp < recList[finalID].timestamp) {
						finalID = i;
					}
				}
			}
		}
		if (count > 0) {
			char time[30];
			strPrintTime(time, recList[finalID].timestamp);
			cout << request.code << ": " << time << endl;
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VLT")) {
		int finalID;
		int count = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				count++;
				if (count == 1) {
					finalID = i;
				}
				if (count > 1) {
					if (recList[i].timestamp >= recList[finalID].timestamp) {
						finalID = i;
					}
				}
			}
		}
		if (count > 0) {
			char time[30];
			strPrintTime(time, recList[finalID].timestamp);
			cout << request.code << ": " << time << endl;
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VCR"))
	{
		int count = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				count++;
			}

		}
		if (count > 0) {
			cout << request.code << ": " << count << endl;
		}
		else if (count == 0) { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VCL"))
	{
		double placeHolderX = 0;
		double placeHolderY = 0;
		double distance = 0;
		double distance_error = 0;
		int count = 0;
		int flag = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				count++;
				flag = 1;
				if (count > 1) {
					distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
					if (distance_error >= 0) {
						distance = distance + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
						distance_error = 0;
					}
				}
				placeHolderX = recList[i].x;
				placeHolderY = recList[i].y;
			}
		}
		if (flag == 0) { cout << "not found!" << endl; return true; }
		else {
			cout << request.code << ": " << distance << endl;
		}
	}
	else if (isEqual(request.code, "VMT")) {
		L1List<VRecord> myList;
		int count = 0;
		double distance_error = 0;
		bool flag = false;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				/*count++;
				flag = true;
				if (count == 1) {
				myList.insertHead(recList[i]);
				flag = false;
				}
				else if (count > 1) {
				for (int x = 0; x < myList.getSize(); x++) {
				if (recList[i].timestamp < myList[x].timestamp) {
				myList.insert(x, recList[i]);
				flag = false;
				break;
				}
				}
				}
				if (flag == true) {
				myList.push_back(recList[i]);
				flag = false;
				}*/
				myList.push_back(recList[i]);
			}
		}
		if (myList.getSize() > 1) {
			double placeHolderX = myList[0].x;
			double placeHolderY = myList[0].y;
			int storedID = 0;
			int timeMoving = 0;
			for (int i = 1; i < myList.getSize(); i++) {
				distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, myList[i].y, myList[i].x);
				if (distance_error >= 0.005) {
					timeMoving = timeMoving + (myList[i].timestamp - myList[storedID].timestamp);
					//cout << timeMoving << endl;
					distance_error = 0;
				}
				placeHolderX = myList[i].x;
				placeHolderY = myList[i].y;
				storedID = i;
			}
			cout << request.code << ": " << timeMoving << endl;
		}
		else { cout << request.code << ": " << "not found!" << endl; }
		/*int count = 0;   //Cach nay su dung cho sampledata co thoi gian(timestamp) luu theo dung thu tu
		int tempTime1 = 0;
		int storedID = 0;
		double placeHolderX = 0;
		double placeHolderY = 0;
		if (recList.getSize() > 0) {
		for (int i = 0; i < recList.getSize(); i++) {
		if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
		&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
		count++;
		if (count > 1) {
		if (placeHolderX != recList[i].x || placeHolderY != recList[i].y) {
		tempTime1 = tempTime1 + (recList[i].timestamp - recList[storedID].timestamp);
		}
		}
		placeHolderX = recList[i].x;
		placeHolderY = recList[i].y;
		storedID = i;
		}
		}
		cout << tempTime1 << endl;
		}
		else { cout << "Failed" << endl << endl; }*/
	}
	else if (isEqual(request.code, "VFS")) {
		double distance_error = 0;
		double placeHolderX = 0;
		double placeHolderY = 0;
		int finalID;
		int flag = 0;
		int flag1 = 0;
		int count = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				flag1 = 1;
				count++;
				if (count > 1) {
					distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
					if (distance_error < 0.005) {
						cout << request.code << ": (" << placeHolderX << ", " << placeHolderY << ")" << endl;
						flag = 1;
						distance_error = 0;
						break;
					}
				}
				placeHolderX = recList[i].x;
				placeHolderY = recList[i].y;
			}
		}
		if (flag1 == 0) {
			cout << request.code << ": " << "not found!" << endl;
		}
		else if (flag == 0 && flag1 == 1) {
			cout << request.code << ": " << "non stop!" << endl;
		}
	}
	else if (isEqual(request.code, "VLS"))
	{
		double distance_error = 0;
		double placeHolderX = 0;
		double placeHolderY = 0;
		//int finalID;
		int flag = 0;
		int flag1 = 0;
		int count = 0;
		for (int i = recList.getSize() - 1; i >-1; i--) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				flag1 = 1;
				count++;
				if (count > 1) {
					distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
					if (distance_error < 0.005) {
						cout << request.code << ": (" << recList[i].x << ", " << recList[i].y << ")" << endl;
						flag = 1;
						distance_error = 0;
						break;
					}
					if (distance_error >= 0.005) { distance_error = 0; }
				}
				placeHolderX = recList[i].x;
				placeHolderY = recList[i].y;
			}
		}
		if (flag1 == 0) {
			cout << request.code << ": " << "not found!" << endl;
		}
		else if (flag == 0 && flag1 == 1) {
			cout << request.code << ": " << "non stop!" << endl;
		}
	}
	else if (isEqual(request.code, "VMS")) {
		L1List<VRecord> myList;
		int count = 0;
		bool flag = false;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				/*count++;
				flag = true;
				if (count == 1) {
				myList.insertHead(recList[i]);
				flag = false;
				}
				else if (count > 1) {
				for (int x = 0; x < myList.getSize(); x++) {
				if (recList[i].timestamp < myList[x].timestamp) {
				myList.insert(x, recList[i]);
				flag = false;
				break;
				}
				}
				}
				if (flag == true) {
				myList.push_back(recList[i]);
				flag = false;
				}*/
				myList.push_back(recList[i]);
			}
		}
		int flag_if_not_move = 1;
		int finalTime = 0;
		double distance_error = 0;
		int tempTime1 = 0;
		if (myList.getSize() > 0) {
			if (myList.getSize() > 1) {

				int storedID = 0;
				double placeHolderX = myList[0].x;
				double placeHolderY = myList[0].y;
				for (int i = 1; i < myList.getSize(); i++) {
					distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, myList[i].y, myList[i].x);
					if (distance_error < 0.005) {
						tempTime1 = tempTime1 + (myList[i].timestamp - myList[storedID].timestamp);
					}
					else if (distance_error >= 0.005) {
						if (tempTime1 > finalTime) { finalTime = tempTime1; }
						distance_error = 0;
						flag_if_not_move = 0;
					}
					placeHolderX = myList[i].x;
					placeHolderY = myList[i].y;
					storedID = i;
				}
			}
			if (flag_if_not_move == 1) {
				cout << request.code << ": " << tempTime1 << endl;
			}
			else if (finalTime > 0 && flag_if_not_move == 0) {
				cout << request.code << ": " << finalTime << endl;
			}
			else if (finalTime == 0) {
				cout << request.code << ": " << "non stop!" << endl;
			}
		}
		else { cout << "not found!" << endl; }
	}
	else if (isEqual(request.code, "VAS"))
	{
		double placeHolderX = 0;
		double placeHolderY = 0;
		double distance = 0;
		double distance_error = 0;
		int count = 0;
		int movingTimes = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				count++;
				if (count > 1) {
					distance_error = distance_error + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
					if (distance_error >= -1) {
						movingTimes++;
						distance = distance + distanceVR(placeHolderY, placeHolderX, recList[i].y, recList[i].x);
						distance_error = 0;
					}
				}
				placeHolderX = recList[i].x;
				placeHolderY = recList[i].y;
			}
		}
		if (movingTimes > 1) {
			distance = distance / movingTimes;
		}
		if (count > 0) {
			cout << request.code << ": " << distance * 1000 << " meter" << endl;
		}
		else { cout << request.code << ": " << "not found!" << endl; }
	}
	else if (isEqual(request.code, "MST")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_MST(recList);
		//code_MST(recList);
		/*L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
		if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
		myList51B04.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
		myList51B06.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
		myList51B0.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
		myList51B14.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
		myList51B1.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
		myList51B.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
		myList51C.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
		myList53N3.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
		myList53N4.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
		myList53N.push_back(recList[n]);
		}
		else {
		myList.push_back(recList[n]);
		}
		}
		int finalNemo = 0;
		int nemo51B04 = findingNemo(myList51B04);
		finalNemo = nemo51B04;

		int nemo51B06 = findingNemo(myList51B06);
		if (nemo51B06 > finalNemo) { finalNemo = nemo51B06; }

		int nemo51B0 = findingNemo(myList51B0);
		if (nemo51B0 > finalNemo) { finalNemo = nemo51B0; }

		int nemo51B14 = findingNemo(myList51B14);
		if (nemo51B14 > finalNemo) { finalNemo = nemo51B14; }

		int nemo51B1 = findingNemo(myList51B1);
		if (nemo51B1 > finalNemo) { finalNemo = nemo51B1; }

		int nemo51B = findingNemo(myList51B);
		if (nemo51B > finalNemo) { finalNemo = nemo51B; }

		int nemo51C = findingNemo(myList51C);
		if (nemo51C > finalNemo) { finalNemo = nemo51C; }

		int nemo53N3 = findingNemo(myList53N3);
		if (nemo53N3 > finalNemo) { finalNemo = nemo53N3; }

		int nemo53N4 = findingNemo(myList53N4);
		if (nemo53N4 > finalNemo) { finalNemo = nemo53N4; }

		int nemo53N = findingNemo(myList53N);
		if (nemo53N > finalNemo) { finalNemo = nemo53N; }

		int nemo = findingNemo(myList);
		if (nemo > finalNemo) { finalNemo = nemo; }

		cout << request.code << ": " << finalNemo << endl;*/


	}
	else if (isEqual(request.code, "CNR")) {
		cout << request.code << ": " << recList.getSize() << endl;
	}
	else if (isEqual(request.code, "MRV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_MRV(recList);
		/*L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
		if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
		myList51B04.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
		myList51B06.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
		myList51B0.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
		myList51B14.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
		myList51B1.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
		myList51B.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
		myList51C.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
		myList53N3.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
		myList53N4.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
		myList53N.push_back(recList[n]);
		}
		else {
		myList.push_back(recList[n]);
		}
		}
		int finalCount = 0;
		int finalID = 0;
		int flag = 0;

		int count51B04 = 0;
		int tempCount51B04 = 0;
		int storedID51B04 = 0;
		for (int i = 0; i < myList51B04.getSize(); i++) {
		tempCount51B04 = 0;
		for (int x = i; x < myList51B04.getSize(); x++) {
		if (myList51B04[i].id[0] == myList51B04[x].id[0] && myList51B04[i].id[1] == myList51B04[x].id[1] && myList51B04[i].id[2] == myList51B04[x].id[2] && myList51B04[i].id[3] == myList51B04[x].id[3] && myList51B04[i].id[4] == myList51B04[x].id[4]
		&& myList51B04[i].id[5] == myList51B04[x].id[5] && myList51B04[i].id[6] == myList51B04[x].id[6] && myList51B04[i].id[7] == myList51B04[x].id[7]) {
		tempCount51B04++;
		}
		}
		if (tempCount51B04 > count51B04) {
		count51B04 = tempCount51B04;
		storedID51B04 = i;
		}
		}
		finalID = storedID51B04; finalCount = count51B04; flag = 1;

		int count51B06 = 0;
		int tempCount51B06 = 0;
		int storedID51B06 = 0;
		for (int i = 0; i < myList51B06.getSize(); i++) {
		tempCount51B06 = 0;
		for (int x = i; x < myList51B06.getSize(); x++) {
		if (myList51B06[i].id[0] == myList51B06[x].id[0] && myList51B06[i].id[1] == myList51B06[x].id[1] && myList51B06[i].id[2] == myList51B06[x].id[2] && myList51B06[i].id[3] == myList51B06[x].id[3] && myList51B06[i].id[4] == myList51B06[x].id[4]
		&& myList51B06[i].id[5] == myList51B06[x].id[5] && myList51B06[i].id[6] == myList51B06[x].id[6] && myList51B06[i].id[7] == myList51B06[x].id[7]) {
		tempCount51B06++;
		}
		}
		if (tempCount51B06 > count51B06) {
		count51B06 = tempCount51B06;
		storedID51B06 = i;
		}
		}
		if (count51B06 > finalCount) { finalID = storedID51B06; finalCount = count51B06; flag = 2; }

		int count51B0 = 0;
		int tempCount51B0 = 0;
		int storedID51B0 = 0;
		for (int i = 0; i < myList51B0.getSize(); i++) {
		tempCount51B0 = 0;
		for (int x = i; x < myList51B0.getSize(); x++) {
		if (myList51B0[i].id[0] == myList51B0[x].id[0] && myList51B0[i].id[1] == myList51B0[x].id[1] && myList51B0[i].id[2] == myList51B0[x].id[2] && myList51B0[i].id[3] == myList51B0[x].id[3] && myList51B0[i].id[4] == myList51B0[x].id[4]
		&& myList51B0[i].id[5] == myList51B0[x].id[5] && myList51B0[i].id[6] == myList51B0[x].id[6] && myList51B0[i].id[7] == myList51B0[x].id[7]) {
		tempCount51B0++;
		}
		}
		if (tempCount51B0 > count51B0) {
		count51B0 = tempCount51B0;
		storedID51B0 = i;
		}
		}
		if (count51B0 > finalCount) { finalID = storedID51B0; finalCount = count51B0; flag = 3; }

		int count51B14 = 0;
		int tempCount51B14 = 0;
		int storedID51B14 = 0;
		for (int i = 0; i < myList51B14.getSize(); i++) {
		tempCount51B14 = 0;
		for (int x = i; x < myList51B14.getSize(); x++) {
		if (myList51B14[i].id[0] == myList51B14[x].id[0] && myList51B14[i].id[1] == myList51B14[x].id[1] && myList51B14[i].id[2] == myList51B14[x].id[2] && myList51B14[i].id[3] == myList51B14[x].id[3] && myList51B14[i].id[4] == myList51B14[x].id[4]
		&& myList51B14[i].id[5] == myList51B14[x].id[5] && myList51B14[i].id[6] == myList51B14[x].id[6] && myList51B14[i].id[7] == myList51B14[x].id[7]) {
		tempCount51B14++;
		}
		}
		if (tempCount51B14 > count51B14) {
		count51B14 = tempCount51B14;
		storedID51B14 = i;
		}
		}
		if (count51B14 > finalCount) { finalID = storedID51B14; finalCount = count51B14; flag = 4; }

		int count51B1 = 0;
		int tempCount51B1 = 0;
		int storedID51B1 = 0;
		for (int i = 0; i < myList51B1.getSize(); i++) {
		tempCount51B1 = 0;
		for (int x = i; x < myList51B1.getSize(); x++) {
		if (myList51B1[i].id[0] == myList51B1[x].id[0] && myList51B1[i].id[1] == myList51B1[x].id[1] && myList51B1[i].id[2] == myList51B1[x].id[2] && myList51B1[i].id[3] == myList51B1[x].id[3] && myList51B1[i].id[4] == myList51B1[x].id[4]
		&& myList51B1[i].id[5] == myList51B1[x].id[5] && myList51B1[i].id[6] == myList51B1[x].id[6] && myList51B1[i].id[7] == myList51B1[x].id[7]) {
		tempCount51B1++;
		}
		}
		if (tempCount51B1 > count51B1) {
		count51B1 = tempCount51B1;
		storedID51B1 = i;
		}
		}
		if (count51B1 > finalCount) { finalID = storedID51B1; finalCount = count51B1; flag = 5; }

		int count51B = 0;
		int tempCount51B = 0;
		int storedID51B = 0;
		for (int i = 0; i < myList51B.getSize(); i++) {
		tempCount51B = 0;
		for (int x = i; x < myList51B.getSize(); x++) {
		if (myList51B[i].id[0] == myList51B[x].id[0] && myList51B[i].id[1] == myList51B[x].id[1] && myList51B[i].id[2] == myList51B[x].id[2] && myList51B[i].id[3] == myList51B[x].id[3] && myList51B[i].id[4] == myList51B[x].id[4]
		&& myList51B[i].id[5] == myList51B[x].id[5] && myList51B[i].id[6] == myList51B[x].id[6] && myList51B[i].id[7] == myList51B[x].id[7]) {
		tempCount51B++;
		}
		}
		if (tempCount51B > count51B) {
		count51B = tempCount51B;
		storedID51B = i;
		}
		}
		if (count51B > finalCount) { finalID = storedID51B; finalCount = count51B; flag = 6; }

		int count51C = 0;
		int tempCount51C = 0;
		int storedID51C = 0;
		for (int i = 0; i < myList51C.getSize(); i++) {
		tempCount51C = 0;
		for (int x = i; x < myList51C.getSize(); x++) {
		if (myList51C[i].id[0] == myList51C[x].id[0] && myList51C[i].id[1] == myList51C[x].id[1] && myList51C[i].id[2] == myList51C[x].id[2] && myList51C[i].id[3] == myList51C[x].id[3] && myList51C[i].id[4] == myList51C[x].id[4]
		&& myList51C[i].id[5] == myList51C[x].id[5] && myList51C[i].id[6] == myList51C[x].id[6] && myList51C[i].id[7] == myList51C[x].id[7]) {
		tempCount51C++;
		}
		}
		if (tempCount51C > count51C) {
		count51C = tempCount51C;
		storedID51C = i;
		}
		}
		if (count51C > finalCount) { finalID = storedID51C; finalCount = count51C; flag = 7; }

		int count53N3 = 0;
		int tempCount53N3 = 0;
		int storedID53N3 = 0;
		for (int i = 0; i < myList53N3.getSize(); i++) {
		tempCount53N3 = 0;
		for (int x = i; x < myList53N3.getSize(); x++) {
		if (myList53N3[i].id[0] == myList53N3[x].id[0] && myList53N3[i].id[1] == myList53N3[x].id[1] && myList53N3[i].id[2] == myList53N3[x].id[2] && myList53N3[i].id[3] == myList53N3[x].id[3] && myList53N3[i].id[4] == myList53N3[x].id[4]
		&& myList53N3[i].id[5] == myList53N3[x].id[5] && myList53N3[i].id[6] == myList53N3[x].id[6] && myList53N3[i].id[7] == myList53N3[x].id[7]) {
		tempCount53N3++;
		}
		}
		if (tempCount53N3 > count53N3) {
		count53N3 = tempCount53N3;
		storedID53N3 = i;
		}
		}
		if (count53N3 > finalCount) { finalID = storedID53N3; finalCount = count53N3; flag = 8; }

		int count53N4 = 0;
		int tempCount53N4 = 0;
		int storedID53N4 = 0;
		for (int i = 0; i < myList53N4.getSize(); i++) {
		tempCount53N4 = 0;
		for (int x = i; x < myList53N4.getSize(); x++) {
		if (myList53N4[i].id[0] == myList53N4[x].id[0] && myList53N4[i].id[1] == myList53N4[x].id[1] && myList53N4[i].id[2] == myList53N4[x].id[2] && myList53N4[i].id[3] == myList53N4[x].id[3] && myList53N4[i].id[4] == myList53N4[x].id[4]
		&& myList53N4[i].id[5] == myList53N4[x].id[5] && myList53N4[i].id[6] == myList53N4[x].id[6] && myList53N4[i].id[7] == myList53N4[x].id[7]) {
		tempCount53N4++;
		}
		}
		if (tempCount53N4 > count53N4) {
		count53N4 = tempCount53N4;
		storedID53N4 = i;
		}
		}
		if (count53N4 > finalCount) { finalID = storedID53N4; finalCount = count53N4; flag = 9; }

		int count53N = 0;
		int tempCount53N = 0;
		int storedID53N = 0;
		for (int i = 0; i < myList53N.getSize(); i++) {
		tempCount53N = 0;
		for (int x = i; x < myList53N.getSize(); x++) {
		if (myList53N[i].id[0] == myList53N[x].id[0] && myList53N[i].id[1] == myList53N[x].id[1] && myList53N[i].id[2] == myList53N[x].id[2] && myList53N[i].id[3] == myList53N[x].id[3] && myList53N[i].id[4] == myList53N[x].id[4]
		&& myList53N[i].id[5] == myList53N[x].id[5] && myList53N[i].id[6] == myList53N[x].id[6] && myList53N[i].id[7] == myList53N[x].id[7]) {
		tempCount53N++;
		}
		}
		if (tempCount53N > count53N) {
		count53N = tempCount53N;
		storedID53N = i;
		}
		}
		if (count53N > finalCount) { finalID = storedID53N; finalCount = count53N; flag = 10; }

		int count = 0;
		int tempCount = 0;
		int storedID = 0;
		for (int i = 0; i < myList.getSize(); i++) {
		tempCount = 0;
		for (int x = i; x < myList.getSize(); x++) {
		if (myList[i].id[0] == myList[x].id[0] && myList[i].id[1] == myList[x].id[1] && myList[i].id[2] == myList[x].id[2] && myList[i].id[3] == myList[x].id[3] && myList[i].id[4] == myList[x].id[4]
		&& myList[i].id[5] == myList[x].id[5] && myList[i].id[6] == myList[x].id[6] && myList[i].id[7] == myList[x].id[7]) {
		tempCount++;
		}
		}
		if (tempCount > count) {
		count = tempCount;
		storedID = i;
		}
		}
		if (count > finalCount) { finalID = storedID; finalCount = count; flag = 11; }

		if (flag == 1) { cout << myList51B04[finalID].id << endl << endl; }
		else if (flag == 2) { cout << myList51B06[finalID].id << endl << endl; }
		else if (flag == 3) { cout << myList51B0[finalID].id << endl << endl; }
		else if (flag == 4) { cout << myList51B14[finalID].id << endl << endl; }
		else if (flag == 5) { cout << myList51B1[finalID].id << endl << endl; }
		else if (flag == 6) { cout << myList51B[finalID].id << endl << endl; }
		else if (flag == 7) { cout << myList51C[finalID].id << endl << endl; }
		else if (flag == 8) { cout << myList53N3[finalID].id << endl << endl; }
		else if (flag == 9) { cout << myList53N4[finalID].id << endl << endl; }
		else if (flag == 10) { cout << myList53N[finalID].id << endl << endl; }
		else if (flag == 11) { cout << myList[finalID].id << endl << endl; }*/
	}
	else if (isEqual(request.code, "LRV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_LRV(recList);
		/*int tempCount1;
		int count1 = recList.getSize();
		int storedID1;
		for (int i = 0; i < recList.getSize(); i++) {
		tempCount1 = 0;
		for (int x = i; x < recList.getSize(); x++) {
		if (recList[i].id[0] == recList[x].id[0] && recList[i].id[1] == recList[x].id[1] && recList[i].id[2] == recList[x].id[2] && recList[i].id[3] == recList[x].id[3] && recList[i].id[4] == recList[x].id[4]
		&& recList[i].id[5] == recList[x].id[5] && recList[i].id[6] == recList[x].id[6] && recList[i].id[7] == recList[x].id[7]) {
		tempCount1++;
		}
		}
		if (tempCount1 == 1) {
		cout << recList[i].id << endl << endl;
		return true;
		}
		}

		L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
		if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
		myList51B04.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
		myList51B06.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
		myList51B0.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
		myList51B14.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
		myList51B1.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
		myList51B.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
		myList51C.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
		myList53N3.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
		myList53N4.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
		myList53N.push_back(recList[n]);
		}
		else {
		myList.push_back(recList[n]);
		}
		}
		int finalCount = 0;
		int finalID = 0;

		int count51B04 = myList51B04.getSize();
		int tempCount51B04 = 0;
		int storedID51B04 = 0;
		for (int i = 0; i < myList51B04.getSize(); i++) {
		tempCount51B04 = 0;
		for (int x = i; x < myList51B04.getSize(); x++) {
		if (myList51B04[i].id[0] == myList51B04[x].id[0] && myList51B04[i].id[1] == myList51B04[x].id[1] && myList51B04[i].id[2] == myList51B04[x].id[2] && myList51B04[i].id[3] == myList51B04[x].id[3] && myList51B04[i].id[4] == myList51B04[x].id[4]
		&& myList51B04[i].id[5] == myList51B04[x].id[5] && myList51B04[i].id[6] == myList51B04[x].id[6] && myList51B04[i].id[7] == myList51B04[x].id[7]) {
		tempCount51B04++;
		}
		}
		if (tempCount51B04 < count51B04) {
		count51B04 = tempCount51B04;
		storedID51B04 = i;
		}
		}
		finalID = storedID51B04; finalCount = count51B04;

		int count51B06 = myList51B06.getSize();
		int tempCount51B06 = 0;
		int storedID51B06 = 0;
		for (int i = 0; i < myList51B06.getSize(); i++) {
		tempCount51B06 = 0;
		for (int x = i; x < myList51B06.getSize(); x++) {
		if (myList51B06[i].id[0] == myList51B06[x].id[0] && myList51B06[i].id[1] == myList51B06[x].id[1] && myList51B06[i].id[2] == myList51B06[x].id[2] && myList51B06[i].id[3] == myList51B06[x].id[3] && myList51B06[i].id[4] == myList51B06[x].id[4]
		&& myList51B06[i].id[5] == myList51B06[x].id[5] && myList51B06[i].id[6] == myList51B06[x].id[6] && myList51B06[i].id[7] == myList51B06[x].id[7]) {
		tempCount51B06++;
		}
		}
		if (tempCount51B06 < count51B06) {
		count51B06 = tempCount51B06;
		storedID51B06 = i;
		}
		}
		if (count51B06 < finalCount) { finalID = storedID51B06; finalCount = count51B06; }

		int count51B0 = myList51B0.getSize();
		int tempCount51B0 = 0;
		int storedID51B0 = 0;
		for (int i = 0; i < myList51B0.getSize(); i++) {
		tempCount51B0 = 0;
		for (int x = i; x < myList51B0.getSize(); x++) {
		if (myList51B0[i].id[0] == myList51B0[x].id[0] && myList51B0[i].id[1] == myList51B0[x].id[1] && myList51B0[i].id[2] == myList51B0[x].id[2] && myList51B0[i].id[3] == myList51B0[x].id[3] && myList51B0[i].id[4] == myList51B0[x].id[4]
		&& myList51B0[i].id[5] == myList51B0[x].id[5] && myList51B0[i].id[6] == myList51B0[x].id[6] && myList51B0[i].id[7] == myList51B0[x].id[7]) {
		tempCount51B0++;
		}
		}
		if (tempCount51B0 < count51B0) {
		count51B0 = tempCount51B0;
		storedID51B0 = i;
		}
		}
		if (count51B0 < finalCount) { finalID = storedID51B0; finalCount = count51B0; }

		int count51B14 = myList51B14.getSize();
		int tempCount51B14 = 0;
		int storedID51B14 = 0;
		for (int i = 0; i < myList51B14.getSize(); i++) {
		tempCount51B14 = 0;
		for (int x = i; x < myList51B14.getSize(); x++) {
		if (myList51B14[i].id[0] == myList51B14[x].id[0] && myList51B14[i].id[1] == myList51B14[x].id[1] && myList51B14[i].id[2] == myList51B14[x].id[2] && myList51B14[i].id[3] == myList51B14[x].id[3] && myList51B14[i].id[4] == myList51B14[x].id[4]
		&& myList51B14[i].id[5] == myList51B14[x].id[5] && myList51B14[i].id[6] == myList51B14[x].id[6] && myList51B14[i].id[7] == myList51B14[x].id[7]) {
		tempCount51B14++;
		}
		}
		if (tempCount51B14 < count51B14) {
		count51B14 = tempCount51B14;
		storedID51B14 = i;
		}
		}
		if (count51B14 < finalCount) { finalID = storedID51B14; finalCount = count51B14; }

		int count51B1 = myList51B1.getSize();
		int tempCount51B1 = 0;
		int storedID51B1 = 0;
		for (int i = 0; i < myList51B1.getSize(); i++) {
		tempCount51B1 = 0;
		for (int x = i; x < myList51B1.getSize(); x++) {
		if (myList51B1[i].id[0] == myList51B1[x].id[0] && myList51B1[i].id[1] == myList51B1[x].id[1] && myList51B1[i].id[2] == myList51B1[x].id[2] && myList51B1[i].id[3] == myList51B1[x].id[3] && myList51B1[i].id[4] == myList51B1[x].id[4]
		&& myList51B1[i].id[5] == myList51B1[x].id[5] && myList51B1[i].id[6] == myList51B1[x].id[6] && myList51B1[i].id[7] == myList51B1[x].id[7]) {
		tempCount51B1++;
		}
		}
		if (tempCount51B1 < count51B1) {
		count51B1 = tempCount51B1;
		storedID51B1 = i;
		}
		}
		if (count51B1 < finalCount) { finalID = storedID51B1; finalCount = count51B1; }

		int count51B = myList51B.getSize();
		int tempCount51B = 0;
		int storedID51B = 0;
		for (int i = 0; i < myList51B.getSize(); i++) {
		tempCount51B = 0;
		for (int x = i; x < myList51B.getSize(); x++) {
		if (myList51B[i].id[0] == myList51B[x].id[0] && myList51B[i].id[1] == myList51B[x].id[1] && myList51B[i].id[2] == myList51B[x].id[2] && myList51B[i].id[3] == myList51B[x].id[3] && myList51B[i].id[4] == myList51B[x].id[4]
		&& myList51B[i].id[5] == myList51B[x].id[5] && myList51B[i].id[6] == myList51B[x].id[6] && myList51B[i].id[7] == myList51B[x].id[7]) {
		tempCount51B++;
		}
		}
		if (tempCount51B < count51B) {
		count51B = tempCount51B;
		storedID51B = i;
		}
		}
		if (count51B < finalCount) { finalID = storedID51B; finalCount = count51B; }

		int count51C = myList51C.getSize();
		int tempCount51C = 0;
		int storedID51C = 0;
		for (int i = 0; i < myList51C.getSize(); i++) {
		tempCount51C = 0;
		for (int x = i; x < myList51C.getSize(); x++) {
		if (myList51C[i].id[0] == myList51C[x].id[0] && myList51C[i].id[1] == myList51C[x].id[1] && myList51C[i].id[2] == myList51C[x].id[2] && myList51C[i].id[3] == myList51C[x].id[3] && myList51C[i].id[4] == myList51C[x].id[4]
		&& myList51C[i].id[5] == myList51C[x].id[5] && myList51C[i].id[6] == myList51C[x].id[6] && myList51C[i].id[7] == myList51C[x].id[7]) {
		tempCount51C++;
		}
		}
		if (tempCount51C < count51C) {
		count51C = tempCount51C;
		storedID51C = i;
		}
		}
		if (count51C < finalCount) { finalID = storedID51C; finalCount = count51C; }

		int count53N3 = myList53N3.getSize();
		int tempCount53N3 = 0;
		int storedID53N3 = 0;
		for (int i = 0; i < myList53N3.getSize(); i++) {
		tempCount53N3 = 0;
		for (int x = i; x < myList53N3.getSize(); x++) {
		if (myList53N3[i].id[0] == myList53N3[x].id[0] && myList53N3[i].id[1] == myList53N3[x].id[1] && myList53N3[i].id[2] == myList53N3[x].id[2] && myList53N3[i].id[3] == myList53N3[x].id[3] && myList53N3[i].id[4] == myList53N3[x].id[4]
		&& myList53N3[i].id[5] == myList53N3[x].id[5] && myList53N3[i].id[6] == myList53N3[x].id[6] && myList53N3[i].id[7] == myList53N3[x].id[7]) {
		tempCount53N3++;
		}
		}
		if (tempCount53N3 < count53N3) {
		count53N3 = tempCount53N3;
		storedID53N3 = i;
		}
		}
		if (count53N3 < finalCount) { finalID = storedID53N3; finalCount = count53N3; }

		int count53N4 = myList53N4.getSize();
		int tempCount53N4 = 0;
		int storedID53N4 = 0;
		for (int i = 0; i < myList53N4.getSize(); i++) {
		tempCount53N4 = 0;
		for (int x = i; x < myList53N4.getSize(); x++) {
		if (myList53N4[i].id[0] == myList53N4[x].id[0] && myList53N4[i].id[1] == myList53N4[x].id[1] && myList53N4[i].id[2] == myList53N4[x].id[2] && myList53N4[i].id[3] == myList53N4[x].id[3] && myList53N4[i].id[4] == myList53N4[x].id[4]
		&& myList53N4[i].id[5] == myList53N4[x].id[5] && myList53N4[i].id[6] == myList53N4[x].id[6] && myList53N4[i].id[7] == myList53N4[x].id[7]) {
		tempCount53N4++;
		}
		}
		if (tempCount53N4 < count53N4) {
		count53N4 = tempCount53N4;
		storedID53N4 = i;
		}
		}
		if (count53N4 < finalCount) { finalID = storedID53N4; finalCount = count53N4; }

		int count53N = myList53N.getSize();
		int tempCount53N = 0;
		int storedID53N = 0;
		for (int i = 0; i < myList53N.getSize(); i++) {
		tempCount53N = 0;
		for (int x = i; x < myList53N.getSize(); x++) {
		if (myList53N[i].id[0] == myList53N[x].id[0] && myList53N[i].id[1] == myList53N[x].id[1] && myList53N[i].id[2] == myList53N[x].id[2] && myList53N[i].id[3] == myList53N[x].id[3] && myList53N[i].id[4] == myList53N[x].id[4]
		&& myList53N[i].id[5] == myList53N[x].id[5] && myList53N[i].id[6] == myList53N[x].id[6] && myList53N[i].id[7] == myList53N[x].id[7]) {
		tempCount53N++;
		}
		}
		if (tempCount53N < count53N) {
		count53N = tempCount53N;
		storedID53N = i;
		}
		}
		if (count53N < finalCount) { finalID = storedID53N; finalCount = count53N; }

		int count = myList.getSize();
		int tempCount = 0;
		int storedID = 0;
		for (int i = 0; i < myList.getSize(); i++) {
		tempCount = 0;
		for (int x = i; x < myList.getSize(); x++) {
		if (myList[i].id[0] == myList[x].id[0] && myList[i].id[1] == myList[x].id[1] && myList[i].id[2] == myList[x].id[2] && myList[i].id[3] == myList[x].id[3] && myList[i].id[4] == myList[x].id[4]
		&& myList[i].id[5] == myList[x].id[5] && myList[i].id[6] == myList[x].id[6] && myList[i].id[7] == myList[x].id[7]) {
		tempCount++;
		}
		}
		if (tempCount < count) {
		count = tempCount;
		storedID = i;
		}
		}
		if (count < finalCount) { finalID = storedID; finalCount = count; }

		for (int i = 0; i < recList.getSize(); i++) {
		tempCount = 0;
		for (int x = i; x < recList.getSize(); x++) {
		if (recList[i].id[0] == recList[x].id[0] && recList[i].id[1] == recList[x].id[1] && recList[i].id[2] == recList[x].id[2] && recList[i].id[3] == recList[x].id[3] && recList[i].id[4] == recList[x].id[4]
		&& recList[i].id[5] == recList[x].id[5] && recList[i].id[6] == recList[x].id[6] && recList[i].id[7] == recList[x].id[7]) {
		tempCount++;
		}
		}
		if (tempCount == finalCount) {
		cout << recList[i].id << endl << endl;
		return true;
		}
		}*/
	}
	else if (isEqual(request.code, "MTV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_MTV(recList);
		/*L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
		if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
		myList51B04.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
		myList51B06.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
		myList51B0.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
		myList51B14.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
		myList51B1.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
		myList51B.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
		myList51C.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
		myList53N3.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
		myList53N4.push_back(recList[n]);
		}
		else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
		myList53N.push_back(recList[n]);
		}
		else {
		myList.push_back(recList[n]);
		}
		}
		int flag = 0;
		int finalDory = 0;
		int dory51B04 = findingDory(myList51B04);
		finalDory = dory51B04; flag = 1;

		int dory51B06 = findingDory(myList51B06);
		if (dory51B06 > finalDory) { finalDory = dory51B06; flag = 2; }

		int dory51B0 = findingDory(myList51B0);
		if (dory51B0 > finalDory) { finalDory = dory51B0; flag = 3; }

		int dory51B14 = findingDory(myList51B14);
		if (dory51B14 > finalDory) { finalDory = dory51B14; flag = 4; }

		int dory51B1 = findingDory(myList51B1);
		if (dory51B1 > finalDory) { finalDory = dory51B1; flag = 5; }

		int dory51B = findingDory(myList51B);
		if (dory51B > finalDory) { finalDory = dory51B; flag = 6; }

		int dory51C = findingDory(myList51C);
		if (dory51C > finalDory) { finalDory = dory51C; flag = 7; }

		int dory53N3 = findingDory(myList53N3);
		if (dory53N3 > finalDory) { finalDory = dory53N3; flag = 8; }

		int dory53N4 = findingDory(myList53N4);
		if (dory53N4 > finalDory) { finalDory = dory53N4; flag = 9; }

		int dory53N = findingDory(myList53N);
		if (dory53N > finalDory) { finalDory = dory53N; flag = 10; }

		int dory = findingDory(myList);
		if (dory > finalDory) { finalDory = dory; flag = 11; }

		if (flag == 1) { cout << myList51B04[findingDoryID(myList51B04)].id << endl; }
		else if (flag == 2) { cout << myList51B06[findingDoryID(myList51B06)].id << endl; }
		else if (flag == 3) { cout << myList51B0[findingDoryID(myList51B0)].id << endl; }
		else if (flag == 4) { cout << myList51B14[findingDoryID(myList51B14)].id << endl; }
		else if (flag == 5) { cout << myList51B1[findingDoryID(myList51B1)].id << endl; }
		else if (flag == 6) { cout << myList51B[findingDoryID(myList51B)].id << endl; }
		else if (flag == 7) { cout << myList51C[findingDoryID(myList51C)].id << endl; }
		else if (flag == 8) { cout << myList53N3[findingDoryID(myList53N3)].id << endl; }
		else if (flag == 9) { cout << myList53N4[findingDoryID(myList53N4)].id << endl; }
		else if (flag == 10) { cout << myList53N[findingDoryID(myList53N)].id << endl; }
		else if (flag == 11) { cout << myList[findingDoryID(myList)].id << endl; }*/
	}
	else if (isEqual(request.code, "MVV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_MVV(recList);
	}
	else if (isEqual(request.code, "CNS")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_CNS(recList);
	}
	else if (isEqual(request.code, "CAS")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_CAS(recList);
	}
	else if (isEqual(request.code, "LPV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_LPV(recList);
		/*L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
			if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
				myList51B04.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
				myList51B06.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
				myList51B0.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
				myList51B14.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
				myList51B1.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
				myList51B.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
				myList51C.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
				myList53N3.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
				myList53N4.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
				myList53N.push_back(recList[n]);
			}
			else {
				myList.push_back(recList[n]);
			}
		}
		float maxDistance = 0;
		float tempDistance = 0;
		int maxDistanceID = 0;
		int tempDistanceID = 0;
		int flag = 0;

		int ID51B04 = findingMaxDistanceID(myList51B04);
		maxDistance = findingDistance(myList51B04, ID51B04);
		maxDistanceID = ID51B04;
		flag = 1;

		int ID51B06 = findingMaxDistanceID(myList51B06);
		tempDistance = findingDistance(myList51B06, ID51B06);
		tempDistanceID = ID51B06;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 2;
		}

		int ID51B0 = findingMaxDistanceID(myList51B0);
		tempDistance = findingDistance(myList51B0, ID51B0);
		tempDistanceID = ID51B0;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 3;
		}

		int ID51B14 = findingMaxDistanceID(myList51B14);
		tempDistance = findingDistance(myList51B14, ID51B14);
		tempDistanceID = ID51B14;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 4;
		}

		int ID51B1 = findingMaxDistanceID(myList51B1);
		tempDistance = findingDistance(myList51B1, ID51B1);
		tempDistanceID = ID51B1;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 5;
		}

		int ID51B = findingMaxDistanceID(myList51B);
		tempDistance = findingDistance(myList51B, ID51B);
		tempDistanceID = ID51B;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 6;
		}

		int ID51C = findingMaxDistanceID(myList51C);
		tempDistance = findingDistance(myList51C, ID51C);
		tempDistanceID = ID51C;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 7;
		}

		int ID53N3 = findingMaxDistanceID(myList53N3);
		tempDistance = findingDistance(myList53N3, ID53N3);
		tempDistanceID = ID53N3;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 8;
		}

		int ID53N4 = findingMaxDistanceID(myList53N4);
		tempDistance = findingDistance(myList53N4, ID53N4);
		tempDistanceID = ID53N4;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 9;
		}

		int ID53N = findingMaxDistanceID(myList53N);
		tempDistance = findingDistance(myList53N, ID53N);
		tempDistanceID = ID53N;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 10;
		}

		int ID = findingMaxDistanceID(myList);
		tempDistance = findingDistance(myList, ID);
		tempDistanceID = ID;
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
			maxDistanceID = tempDistanceID;
			flag = 11;
		}
		if (flag == 1) { cout << myList51B04[maxDistanceID].id << endl << endl; }
		else if (flag == 2) { cout << request.code << ": " << myList51B06[maxDistanceID].id << endl; }
		else if (flag == 3) { cout << request.code << ": " << myList51B0[maxDistanceID].id << endl; }
		else if (flag == 4) { cout << request.code << ": " << myList51B14[maxDistanceID].id << endl; }
		else if (flag == 5) { cout << request.code << ": " << myList51B1[maxDistanceID].id << endl; }
		else if (flag == 6) { cout << request.code << ": " << myList51B[maxDistanceID].id << endl; }
		else if (flag == 7) { cout << request.code << ": " << myList51C[maxDistanceID].id << endl; }
		else if (flag == 8) { cout << request.code << ": " << myList53N3[maxDistanceID].id << endl; }
		else if (flag == 9) { cout << request.code << ": " << myList53N4[maxDistanceID].id << endl; }
		else if (flag == 10) { cout << request.code << ": " << myList53N[maxDistanceID].id << endl; }
		else if (flag == 11) { cout << request.code << ": " << myList[maxDistanceID].id << endl; }*/
	}
	else if (isEqual(request.code, "SPV")) {
		if (ff == 0)
		{
			code_0(recList, idList);
			ff = 1;
		}
		code_SPV(recList);
		/*L1List<VRecord> myList;
		L1List<VRecord> myList51B04;
		L1List<VRecord> myList51B06;
		L1List<VRecord> myList51B0;
		L1List<VRecord> myList51B14;
		L1List<VRecord> myList51B1;
		L1List<VRecord> myList51B;
		L1List<VRecord> myList51C;
		L1List<VRecord> myList53N3;
		L1List<VRecord> myList53N4;
		L1List<VRecord> myList53N;
		for (int n = 0; n < recList.getSize(); n++) {
			if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '4') {
				myList51B04.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0' && recList[n].id[4] == '6') {
				myList51B06.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '0') {
				myList51B0.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1'  && recList[n].id[4] == '4') {
				myList51B14.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B' && recList[n].id[3] == '1') {
				myList51B1.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'B') {
				myList51B.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '1'&& recList[n].id[2] == 'C') {
				myList51C.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '3') {
				myList53N3.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N' && recList[n].id[3] == '4') {
				myList53N4.push_back(recList[n]);
			}
			else if (recList[n].id[0] == '5' && recList[n].id[1] == '3'&& recList[n].id[2] == 'N') {
				myList53N.push_back(recList[n]);
			}
			else {
				myList.push_back(recList[n]);
			}
		}

		float minDistance = 0;
		float tempDistance = 0;
		int minDistanceID = 0;
		int tempDistanceID = 0;
		int flag = 0;

		int ID51B04 = findingMinDistanceID(myList51B04);
		minDistance = findingDistance(myList51B04, ID51B04);
		minDistanceID = ID51B04;
		flag = 1;

		int ID51B06 = findingMinDistanceID(myList51B06);
		tempDistance = findingDistance(myList51B06, ID51B06);
		tempDistanceID = ID51B06;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 2;
		}

		int ID51B0 = findingMinDistanceID(myList51B0);
		tempDistance = findingDistance(myList51B0, ID51B0);
		tempDistanceID = ID51B0;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 3;
		}

		int ID51B14 = findingMinDistanceID(myList51B14);
		tempDistance = findingDistance(myList51B14, ID51B14);
		tempDistanceID = ID51B14;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 4;
		}

		int ID51B1 = findingMinDistanceID(myList51B1);
		tempDistance = findingDistance(myList51B1, ID51B1);
		tempDistanceID = ID51B1;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 5;
		}

		int ID51B = findingMinDistanceID(myList51B);
		tempDistance = findingDistance(myList51B, ID51B);
		tempDistanceID = ID51B;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 6;
		}

		int ID51C = findingMinDistanceID(myList51C);
		tempDistance = findingDistance(myList51C, ID51C);
		tempDistanceID = ID51C;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 7;
		}

		int ID53N3 = findingMinDistanceID(myList53N3);
		tempDistance = findingDistance(myList53N3, ID53N3);
		tempDistanceID = ID53N3;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 8;
		}

		int ID53N4 = findingMinDistanceID(myList53N4);
		tempDistance = findingDistance(myList53N4, ID53N4);
		tempDistanceID = ID53N4;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 9;
		}

		int ID53N = findingMinDistanceID(myList53N);
		tempDistance = findingDistance(myList53N, ID53N);
		tempDistanceID = ID53N;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 10;
		}

		int ID = findingMinDistanceID(myList);
		tempDistance = findingDistance(myList, ID);
		tempDistanceID = ID;
		if (tempDistance < minDistance) {
			minDistance = tempDistance;
			minDistanceID = tempDistanceID;
			flag = 11;
		}

		if (flag == 1) { cout << myList51B04[minDistanceID].id << endl << endl; }
		else if (flag == 2) { cout << request.code << ": " << myList51B06[minDistanceID].id << endl; }
		else if (flag == 3) { cout << request.code << ": " << myList51B0[minDistanceID].id << endl; }
		else if (flag == 4) { cout << request.code << ": " << myList51B14[minDistanceID].id << endl; }
		else if (flag == 5) { cout << request.code << ": " << myList51B1[minDistanceID].id << endl; }
		else if (flag == 6) { cout << request.code << ": " << myList51B[minDistanceID].id << endl; }
		else if (flag == 7) { cout << request.code << ": " << myList51C[minDistanceID].id << endl; }
		else if (flag == 8) { cout << request.code << ": " << myList53N3[minDistanceID].id << endl; }
		else if (flag == 9) { cout << request.code << ": " << myList53N4[minDistanceID].id << endl; }
		else if (flag == 10) { cout << request.code << ": " << myList53N[minDistanceID].id << endl; }
		else if (flag == 11) { cout << request.code << ": " << myList[minDistanceID].id << endl; }*/
	}
	else if (isEqual(request.code, "RVR")) {
		int flag = 0;
		for (int i = 0; i < recList.getSize(); i++) {
			if (recList[i].id[0] == request.code[3] && recList[i].id[1] == request.code[4] && recList[i].id[2] == request.code[5] && recList[i].id[3] == request.code[6] && recList[i].id[4] == request.code[7]
				&& recList[i].id[5] == request.code[8] && recList[i].id[6] == request.code[9] && recList[i].id[7] == request.code[10]) {
				recList.remove(i);
				flag = 1;
			}
		}
		code_0(recList, idList);
		ff = 1;
		if (flag == 1) {
			cout << request.code << ": " << "success!" << endl;
		}
		else cout << request.code << ": " << "not found!" << endl;
	}
	else { cout << request.code << ": " << "not found!" << endl; }
	//mvv cns cas
	/// NOTE: The output of the request will be printed on one line
	/// end by the end-line '\n' character.
	return true;
}