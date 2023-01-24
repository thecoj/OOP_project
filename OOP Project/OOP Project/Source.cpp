#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include "identificator.h"
#include <fstream>
#include "TextFile.h"
#include "BinaryFile.h"
#include "Data.h"
#include "Column.h"
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <exception>
#include "Index.h"
using namespace std;

int CreateTable(char* tableName, char* tableInfo, list<string>& columns, int* size, char* command, list<string>& columnType);
int DropTable(char* tableName, char* command, int tokenType);
int DisplayTable(char* tableName, char* command);
char Delete(char check, char* tableName, char* nameColumnWhere, char* valueWhere, int& typeWhere, char* command, int tokenType);
int Update(char* tableName, char* columnNameSet, char* valueSet, int& setType, char* nameColumnWhere, char* valueWhere, int& typeWhere, char* command, char* tableInfo);
int Select(char* tableName, char* command, char* columns);
int Insert(char* tableName, char* command, char* values, vector<int>& valueTypes);
int Import(char* tableName, char* command, char* fileName);
int DropIndex(char* command, char* tableName, char* indexName, int tokenType);
int CreateIndex(char* tableName, char* indexName, char* columnName, char* command);
void CreateBinary(char* tableName, char* tableInfo);

int main(int argc, char* argv[])
{
	map<string, list<string>> mapDB_Columns, mapDB_Type;
	map<string, multiset<int>> mapInt;
	map<string, multiset<float>> mapFloat;
	map<string, multiset<string>> mapString;
	map<string, multiset<int>> mapIndexInt;
	map<string, multiset<float>> mapIndexFloat;
	map<string, multiset<string>> mapIndexString;
	multiset<int> setInt; multiset<float> setFloat; multiset<string> setString;
	char* input, token;
	char* p;
	char* line;
	char in[10000];
	int tokenType, existed, type, sel = 0, setType, typeWhere;
	TextFile f; FILE* e; BinaryFile k; Column c; BinaryFileOut z; TextFileCommands hCommands;

	int result = 0; char check = 'O';
	char tableInfo[100] = { '\0' };
	char tableName[100] = { '\0' };
	char indexName[100] = { '\0' };
	char importName[100] = { '\0' };
	char nameColumnWhere[100] = { '\0' };
	char columnName[100] = { '\0' };
	char columnNameSet[100] = { '\0' };
	char columns[1000] = { '\0' };
	char values[1000] = { '\0' };
	char valueWhere[100] = { '\0' };
	char valueSet[100] = { '\0' };


	if (argc > 6)
	{
		printf("ERROR: too many files for input in main");
		return 0;
	}
	else
	{
		if (argc == 1)
		{
			/*string fi = "BINARY.bin",af;
			fstream w;bool ok = 1;
			w.open(fi, ios::in | ios::binary);
			//while (!w.eof())
			while (!w.eof())
			{
				getline(w, af);
				cout << af;
			}
			 /*string fi = "DATA.csv", af;
			 fstream w;bool ok = 1;
			 w.open(fi, ios::in | ios::binary);
			 //while (!w.eof())
			 while (!w.eof())
			 {
				 getline(w, af);
				 cout << af<<endl;// << " " << af.find(',') << "//";
				 char* o;
				 o = strtok((char*)af.c_str(), " ");
				 while (o != NULL)
				 {
					 if (o[strlen(o) - 1] == ',')
					 {
						 cout << o << " " << o[strlen(o) - 1]<<endl;
						 o = strtok(NULL, " ");
					 }
					 else
					 {
						// cout << "another found";
						 ok = 0;
						 break;
					 }
				 }
				 cout << o<<endl;
				 string aff;
				 aff = af.substr(af.length() - 1);
				cout << aff<<aff.c_str()<<endl;

				if (ok == 0)
					if (strcmp(o, aff.c_str()))
						cout << "another";
					else
						cout << "success";
				//if (strcmp(o, aff.c_str()) != 0)
				//	cout << "another delimiter found";
			 }
			 w.close();
			//w.open(fi, ios::out | ios::trunc | ios::binary);
			//w << fi<<endl;
			//w << 2;
			//w.close();
			//while (w.is_open())
				  //while (getline(w, af))
				//for (int i = 0; i < 5;i++)*/
				/*string keyboard, keyboardCommands;
				cout << "Insert the name of the file where the commands will be stored"<<endl;
				getline(std::cin, keyboard);
				DataCommands dataCommands;

				Data** pointers = nullptr;
				pointers = new Data* [4];
				pointers[0] = &dataCommands;
				pointers[0]->create((char*)keyboard.c_str());
				//dataCommands.create((char*)keyboard.c_str());

				cout << "Insert commands"<<endl;
				getline(std::cin, keyboardCommands);
				DataCommands dataWritingCommands;
				pointers[1] = &dataWritingCommands;
				pointers[1]->write((char*)keyboard.c_str(), keyboardCommands);
				//dataWritingCommands.write((char*)keyboard.c_str(), keyboardCommands);
				//TESTING DATA READING COMMANDS*/
				// Testing Data Import
				/*cout << "Insert CSV file name " << endl;
				getline(std::cin, keyboard);
				DataImport dataImport;
				pointers[2] = &dataImport;
				pointers[2]->create((char*)keyboard.c_str());
				//dataImport.create((char*)keyboard.c_str());

				cout << "Insert values" << endl;
				getline(std::cin, keyboardCommands);
				DataImport dataWritingImport;
				pointers[3] = &dataWritingImport;
				pointers[3]->write((char*)keyboard.c_str(), keyboardCommands);
				//dataWritingImport.write((char*)keyboard.c_str(), keyboardCommands);*/

			std::cout << "Please input your sql command:" << endl;
			string tmp;
			while (std::getline(std::cin, tmp))
			{
				if (tmp.empty())
					break;
				else
				{
					bool moreCommands = 0;
					transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
					input = (char*)tmp.c_str();
					p = strtok(input, " ");
					do
					{
						if (moreCommands)
						{
							input = strtok(NULL, " ");
							if (!input)
							{
								break;
							}
						}
						commandType(input, &tokenType);
						switch (tokenType)
						{
						case CREATE:
						{
							list<string> columnsList, listType;
							commandType(input + 7, &tokenType);
							if (tokenType == TABLE)
							{
								int* size = new int[100];
								result = CreateTable(tableName, tableInfo, columnsList, size, input, listType);
								if (result)
								{
									string name = tableName;
									name += ".txt";
									fstream h(name.c_str(), ios::in);
									if (h.good())
										std::cout << "ERROR: file exists";
									else {
										std::cout << "Table " << tableName << " has been created with the following columns:  " << tableInfo << endl;
										f.fileTextCreate(tableName, tableInfo);
										h.close();
										h.open(name.c_str(), ios::out | ios::app);
										mapDB_Columns.insert(pair<string, list<string>>(tableName, columnsList));
										mapDB_Type.insert(pair<string, list<string>>(tableName, listType));
										for (list<string>::iterator it1 = columnsList.begin(), it2 = listType.begin(); it1 != columnsList.end() && it2 != listType.end(); it1++, it2++)
										{
											h << *it2 << " ";
										}
										h.close();
										h.open(name, ios::in);
										k.fileBinaryCreate(tableName, tableInfo);
										/*for (map<string, list<string>>::iterator it = mapDB_Columns.begin();it != mapDB_Columns.end();it++)
										{
											std::cout << it->first << " columns list" << endl;
										}

										for (map<string, list<string>>::iterator it = mapDB_Type.begin();it != mapDB_Type.end();it++)
										{
											std::cout << it->first << " type list" << endl;
										}*/
										for (list<string>::iterator it1 = columnsList.begin(), it2 = listType.begin(); it1 != columnsList.end(), it2 != listType.end(); it1++, it2++)
										{
											if (*it2 == "INT")
											{
												string name = *it1;
												name += ".";
												name += tableName;
												mapInt.insert(pair<string, multiset<int>>(name, setInt));
											}
											else
												if (*it2 == "FLOAT")
												{
													string name = *it1;
													name += ".";
													name += tableName;
													mapFloat.insert(pair<string, multiset<float>>(name, setFloat));
												}
												else
													if (*it2 == "CHAR")
													{
														string name = *it1;
														name += ".";
														name += tableName;
														mapString.insert(pair<string, multiset<string>>(name, setString));

													}
										}

										//k.fileBinaryDisplay(tableName, tableInfo);
										//intColumn* pint = (intColumn*)&c;
										//pint->display(tableInfo, 
										/*if (type == 1)
											cout << "Column int";
										else
											if (type == 2)
												cout << "Column float";
											else
												if (type == 3)
													cout << "Column string";*/
									}
								}
								break;
							}
							else
							{
								if (tokenType == INDEX)
								{
									result = CreateIndex(tableName, indexName, columnName, input);
									if (result)
									{
										string name = tableName;
										name += ".txt";
										ifstream h(name.c_str());
										if (!h.good())
											cout << "ERROR: table DOES NOT  exist" << endl;
										else
										{
											string nameC = columnName, type; bool isColumn = 0;
											map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
											map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
											list<string>::iterator ic = it1->second.begin(), it = it2->second.begin();
											while (ic != it1->second.end() && it != it2->second.end())
											{
												if (*ic == nameC)
												{
													type = *it;
													isColumn = 1;
													break;
												}
												ic++; it++;
											}
											if (isColumn == 0)
												cout << "The columns does not exist inside the table" << endl;
											else
											{
												IndexInt indI(indexName); IndexFloat indF(indexName); IndexString indS(indexName);
												if (type == "INT")
												{
													//Index* ind =&indI;
													//ind->create();
													indI.create();
													auto it = indI.mapIndexInt.find(indexName);
													mapIndexInt.insert(pair<string, multiset<int>>(indexName, it->second));
												}
												else
													if (type == "FLOAT")
													{
														//Index& ind = indF;
														indF.create();
														auto it = indF.mapIndexFloat.find(indexName);
														mapIndexFloat.insert(pair<string, multiset<float>>(indexName, it->second));

													}
													else
														if (type == "CHAR")
														{
															//Index& ind = indS;
															indS.create();
															auto it = indS.mapIndexString.find(indexName);
															mapIndexString.insert(pair<string, multiset<string>>(indexName, it->second));

														}
											}
											//cout << "The index " << indexName << " has been created for the column " << columnName << " from table " << tableName << endl;

										}
									}
									break;
								}
								else
								{
									cout << "ERROR: TABLE or INDEX  missing\n";
									break;
								}
							}
						}
						case DROP:
						{

							commandType(input + 5, &tokenType);
							if (tokenType == TABLE)
							{
								result = DropTable(tableName, input, tokenType);
								if (result)
								{
									if (remove(tableName) != 0)
									{
										f.fileTextDrop(tableName, existed);
										if (existed == 1)
										{
											string name = tableName;
											map<string, list<string>>::iterator it = mapDB_Columns.find(name);
											if (it != mapDB_Columns.end())
											{
												cout << it->first << endl;
												mapDB_Columns.erase(name);
												mapDB_Type.erase(name);
											}
											cout << "Deleted" << endl;
										}
										else
											cout << "DOES NOT EXIST" << endl;
									}

								}

								break;
							}
							else
							{
								if (tokenType == INDEX)
								{
									result = DropIndex(input, tableName, indexName, tokenType);
									if (result)
									{
										IndexInt indI(indexName); IndexFloat indF(indexName); IndexString indS(indexName);
										//cout << "Index " << indexName << " has been dropped " << endl;
										//Index ind;
										//string nameC = columnName, type;bool isColumn = 0;
										//map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
										//map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
										map<string, multiset<int>>::iterator iti = mapIndexInt.find(indexName);
										//IndexInt indI(indexName);IndexFloat indF(indexName); IndexString indS(indexName);

										if (iti != mapIndexInt.end())
										{
											Index& ind = indI;
											ind.drop();
										}
										else
										{
											map<string, multiset<float>>::iterator itf = mapIndexFloat.find(indexName);
											if (itf != mapIndexFloat.end())
											{
												Index& ind = indF;
												ind.drop();
											}
											else
											{
												map<string, multiset<string>>::iterator its = mapIndexString.find(indexName);
												if (its != mapIndexString.end())
												{
													Index& ind = indS;
													ind.drop();
												}
												else
													cout << "Index to be deleted does not exist" << endl;
											}
										}

									}
									break;
								}
								else
								{
									cout << "ERROR: TABLE or INDEX  missing\n";
									break;
								}
							}
						}
						case DISPLAY:
						{
							result = DisplayTable(tableName, input);
							if (result)
							{
								string name = tableName;
								name += ".txt";
								ifstream h(name.c_str());
								if (!h.good())
									cout << "ERROR: file DOES NOT  exist";
								else
								{
									cout << "Table displayed: " << tableName << endl;
									f.fileTextDisplay(tableName, tableInfo);
									string af;
									while (!h.eof())
									{
										getline(h, af);
										cout << af << endl;
									}
								}
							}
							break;
						}
						case DELETE:
						{
							result = Delete(check, tableName, nameColumnWhere, valueWhere, typeWhere, input, tokenType);
							if ((char)result == 'Y')
							{
								string name = tableName;
								name += ".txt";
								ifstream h(name.c_str());
								if (!h.good())
									cout << "ERROR: file DOES NOT  exist";
								else
								{
									map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
									map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
									string type, nameC = "", aux = "";
									for (int i = 0; i < strlen(nameColumnWhere); i++)
									{
										nameC += nameColumnWhere[i];
										aux += nameColumnWhere[i];
									}
									bool found = 0;
									for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin(); ic != it1->second.end(), it != it2->second.end(); ic++, it++)
									{
										if (nameC == *ic)
										{
											found = 1;
											type = *it;
											break;
										}
									}
									if (found == 0)
										cout << "Column to be deleted does not exist" << endl;
									else
									{
										bool deleted = 0, isType = 1;
										if (typeWhere == INTEGER_NB)
											if (type != "INT")
												isType = 0;
											else
												if (typeWhere == FLOAT_NB)
												{
													if (type != "FLOAT")
														isType = 0;
												}
												else
													if (typeWhere == IDENTIFICATOR)
														if (type != "CHAR")
															isType = 0;
										if (isType == 0)
											cout << "Value to be deleted does not match the value type of the column" << endl;
										else
										{
											nameC += ".";
											nameC += tableName;

											int index = 0, ind = 0;
											if (type == "INT")
											{
												map<string, multiset<int>>::iterator itI = mapInt.find(nameC);
												multiset<int>::iterator iti;
												for (iti = itI->second.begin(); iti != itI->second.end(); iti++)
												{
													index++;
													if (atoi(valueWhere) == *iti)
													{
														itI->second.erase(*iti);
														deleted = 1;
														break;
													}
												}
												for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin(); iter1 != it1->second.end(), iter2 != it2->second.end(); iter1++, iter2++)
												{
													if (*iter1 != aux)
													{
														string namec = *iter1;
														namec += ".";
														namec += tableName;
														if (*iter2 == "INT")
														{
															map<string, multiset<int>>::iterator itInt = mapInt.find(namec);
															multiset<int>::iterator itint = itInt->second.begin();
															while (itint != itInt->second.end())
															{
																ind++;
																if (ind == index)
																{
																	itInt->second.erase(*itint);
																	break;
																}
																itint++;
															}
														}
														else
															if (*iter2 == "FLOAT")
															{
																map<string, multiset<float>>::iterator itFloat = mapFloat.find(namec);
																multiset<float>::iterator itfloat = itFloat->second.begin();
																while (itfloat != itFloat->second.end())
																{
																	ind++;
																	if (ind == index)
																	{
																		itFloat->second.erase(*itfloat);
																		break;
																	}
																	itfloat++;
																}
															}
															else
																if (*iter2 == "CHAR")
																{
																	map<string, multiset<string>>::iterator itString = mapString.find(namec);
																	multiset<string>::iterator itstring = itString->second.begin();
																	while (itstring != itString->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itString->second.erase(*itstring);
																			break;
																		}
																		itstring++;
																	}
																}
													}
												}
											}
											else
												if (type == "FLOAT")
												{
													map<string, multiset<float>>::iterator itF = mapFloat.find(nameC);
													multiset<float>::iterator itf;
													for (itf = itF->second.begin(); itf != itF->second.end(); itf++)
													{
														index++;
														if (atof(valueWhere) == *itf)
														{
															itF->second.erase(*itf);
															deleted = 1;
															break;
														}
													}
													for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin(); iter1 != it1->second.end(), iter2 != it2->second.end(); iter1++, iter2++)
													{
														if (*iter1 != aux)
														{
															string namec = *iter1;
															namec += ".";
															namec += tableName;
															if (*iter2 == "INT")
															{
																map<string, multiset<int>>::iterator itInt = mapInt.find(namec);
																multiset<int>::iterator itint = itInt->second.begin();
																while (itint != itInt->second.end())
																{
																	ind++;
																	if (ind == index)
																	{
																		itInt->second.erase(*itint);
																		break;
																	}
																	itint++;
																}
															}
															else
																if (*iter2 == "FLOAT")
																{
																	map<string, multiset<float>>::iterator itFloat = mapFloat.find(namec);
																	multiset<float>::iterator itfloat = itFloat->second.begin();
																	while (itfloat != itFloat->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itFloat->second.erase(*itfloat);
																			break;
																		}
																		itfloat++;
																	}
																}
																else
																	if (*iter2 == "CHAR")
																	{
																		map<string, multiset<string>>::iterator itString = mapString.find(namec);
																		multiset<string>::iterator itstring = itString->second.begin();
																		while (itstring != itString->second.end())
																		{
																			ind++;
																			if (ind == index)
																			{
																				itString->second.erase(*itstring);
																				break;
																			}
																			itstring++;
																		}
																	}
														}
													}
												}
												else
													if (type == "CHAR")
													{
														map<string, multiset<string>>::iterator itS = mapString.find(nameC);
														multiset<string>::iterator its;
														for (its = itS->second.begin(); its != itS->second.end(); its++)
														{
															index++;
															string val = "";
															for (int i = 0; i < strlen(valueWhere); i++)
																val += valueWhere[i];
															if (val == *its)
															{
																itS->second.erase(*its);
																deleted = 1;
																break;
															}
														}
														for (list<string>::iterator iter1 = it1->second.begin(), iter2 = it2->second.begin(); iter1 != it1->second.end(), iter2 != it2->second.end(); iter1++, iter2++)
														{
															if (*iter1 != aux)
															{
																string namec = *iter1;
																namec += ".";
																namec += tableName;
																if (*iter2 == "INT")
																{
																	map<string, multiset<int>>::iterator itInt = mapInt.find(namec);
																	multiset<int>::iterator itint = itInt->second.begin();
																	while (itint != itInt->second.end())
																	{
																		ind++;
																		if (ind == index)
																		{
																			itInt->second.erase(*itint);
																			break;
																		}
																		itint++;
																	}
																}
																else
																	if (*iter2 == "FLOAT")
																	{
																		map<string, multiset<float>>::iterator itFloat = mapFloat.find(namec);
																		multiset<float>::iterator itfloat = itFloat->second.begin();
																		while (itfloat != itFloat->second.end())
																		{
																			ind++;
																			if (ind == index)
																			{
																				itFloat->second.erase(*itfloat);
																				break;
																			}
																			itfloat++;
																		}
																	}
																	else
																		if (*iter2 == "CHAR")
																		{
																			map<string, multiset<string>>::iterator itString = mapString.find(namec);
																			multiset<string>::iterator itstring = itString->second.begin();
																			while (itstring != itString->second.end())
																			{
																				ind++;
																				if (ind == index)
																				{
																					itString->second.erase(*itstring);
																					break;
																				}
																				itstring++;
																			}
																		}
															}
														}
													}
											if (deleted == 1)
											{
												cout << "Table records deleted from " << tableName << " where the column " << nameColumnWhere << " has the value " << valueWhere << endl;
												k.fileBinaryDisplay(tableName, mapInt, mapFloat, mapString);
											}
											else
												cout << "Value to be deleted does not exist inside the table" << endl;
										}

									}
								}
							}
							break;
						}
						case UPDATE:
						{
							char* tableInfo = new char[10000];
							result = Update(tableName, columnNameSet, valueSet, setType, nameColumnWhere, valueWhere, typeWhere, input, tableInfo);
							if (result)
							{
								string name = tableName;
								name += ".txt";
								ifstream h(name.c_str());
								if (!h.good())
									cout << "ERROR: file DOES NOT  exist";
								else
								{
									map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
									map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
									string typeC, typeS, nameC = "", aux = "", nameS = "";
									for (int i = 0; i < strlen(nameColumnWhere); i++)
										nameC += nameColumnWhere[i];
									for (int i = 0; i < strlen(columnNameSet); i++)
										nameS += columnNameSet[i];
									bool foundC = 0, foundS = 0;
									for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin(); ic != it1->second.end(), it != it2->second.end(); ic++, it++)
									{
										if (nameC == *ic)
										{
											foundC = 1;
											typeC = *it;
											break;
										}
									}
									if (foundC == 0)
										cout << "Conditioning cloumn does not exist inside the table" << endl;
									else
									{

										for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin(); ic != it1->second.end(), it != it2->second.end(); ic++, it++)
										{
											if (nameS == *ic)
											{
												foundS = 1;
												typeS = *it;
												break;
											}
										}
										if (foundS == 0)
											cout << "Column to be updated does not exist inside the table" << endl;
										else
										{
											bool isType = 1;
											if (typeWhere == INTEGER_NB)
											{
												if (typeC != "INT")
													isType = 0;
											}
											else
												if (typeWhere == FLOAT_NB)
												{
													if (typeC != "FLOAT")
														isType = 0;
												}
												else
													if (typeWhere == IDENTIFICATOR)
													{
														if (typeC != "CHAR")
															isType = 0;
													}
											if (isType == 0)
												cout << "Inappropriate value type" << endl;
											else
											{
												bool isTypeS = 1;
												if (setType == INTEGER_NB)
												{
													if (typeS != "INT")
														isTypeS = 0;
												}
												else
													if (setType == FLOAT_NB)
													{
														if (typeS != "FLOAT")
															isTypeS = 0;
													}
													else
														if (setType == IDENTIFICATOR)
														{
															if (typeS != "CHAR")
																isTypeS = 0;
														}
												if (isTypeS == 0)
													cout << "Inappropriate value type" << endl;
												else
												{
													nameC += "."; nameS += ".";
													nameC += tableName; nameS += tableName;
													bool isSet = 1;
													if (typeC == "INT")
													{
														map<string, multiset<int>>::iterator itI = mapInt.find(nameC);
														multiset<int>::iterator iti = itI->second.find(atoi(valueWhere));
														int x = distance(itI->second.begin(), iti);
														if (typeS == "INT")
														{
															map<string, multiset<int>>::iterator itIS = mapInt.find(nameS);
															multiset<int>::iterator itis = itIS->second.begin();
															advance(itis, x);
															if (itis != itIS->second.end())
															{
																itIS->second.erase(*itis);
																itIS->second.insert(atoi(valueSet));
															}
															else
																isSet = 0;
														}
														else
															if (typeS == "FLOAT")
															{
																map<string, multiset<float>>::iterator itFS = mapFloat.find(nameS);
																multiset<float>::iterator itfs = itFS->second.begin();
																advance(itfs, x);
																if (itfs != itFS->second.end())
																{
																	itFS->second.erase(*itfs);
																	itFS->second.insert(atof(valueSet));
																}
																else
																	isSet = 0;
															}
															else
																if (typeS == "CHAR")
																{
																	map<string, multiset<string>>::iterator itSS = mapString.find(nameS);
																	multiset<string>::iterator itss = itSS->second.begin();
																	advance(itss, x);
																	if (itss != itSS->second.end())
																	{
																		itSS->second.erase(*itss);
																		itSS->second.insert(valueSet);
																	}
																	else
																		isSet = 0;
																}
													}
													else
														if (typeC == "FLOAT")
														{
															map<string, multiset<float>>::iterator itF = mapFloat.find(nameC);
															multiset<float>::iterator itf = itF->second.find(atof(valueWhere));
															int x = distance(itF->second.begin(), itf);
															if (typeS == "INT")
															{
																map<string, multiset<int>>::iterator itIS = mapInt.find(nameS);
																multiset<int>::iterator itis = itIS->second.begin();
																advance(itis, x);
																if (itis != itIS->second.end())
																{
																	itIS->second.erase(*itis);
																	itIS->second.insert(atoi(valueSet));
																}
																else
																	isSet = 0;
															}
															else
																if (typeS == "FLOAT")
																{
																	map<string, multiset<float>>::iterator itFS = mapFloat.find(nameS);
																	multiset<float>::iterator itfs = itFS->second.begin();
																	advance(itfs, x);
																	if (itfs != itFS->second.end())
																	{
																		itFS->second.erase(*itfs);
																		itFS->second.insert(atof(valueSet));
																	}
																	else
																		isSet = 0;
																}
																else
																	if (typeS == "CHAR")
																	{
																		map<string, multiset<string>>::iterator itSS = mapString.find(nameS);
																		multiset<string>::iterator itss = itSS->second.begin();
																		advance(itss, x);
																		if (itss != itSS->second.end())
																		{
																			itSS->second.erase(*itss);
																			itSS->second.insert(valueSet);
																		}
																		else
																			isSet = 0;
																	}
														}
														else
															if (typeC == "CHAR")
															{
																map<string, multiset<string>>::iterator itS = mapString.find(nameC);
																multiset<string>::iterator its = itS->second.find(valueWhere);
																int x = distance(itS->second.begin(), its);
																if (typeS == "INT")
																{
																	map<string, multiset<int>>::iterator itIS = mapInt.find(nameS);
																	multiset<int>::iterator itis = itIS->second.begin();
																	advance(itis, x);
																	if (itis != itIS->second.end())
																	{
																		itIS->second.erase(*itis);
																		itIS->second.insert(atoi(valueSet));
																	}
																	else
																		isSet = 0;
																}
																else
																	if (typeS == "FLOAT")
																	{
																		map<string, multiset<float>>::iterator itFS = mapFloat.find(nameS);
																		multiset<float>::iterator itfs = itFS->second.begin();
																		advance(itfs, x);
																		if (itfs != itFS->second.end())
																		{
																			itFS->second.erase(*itfs);
																			itFS->second.insert(atof(valueSet));
																		}
																		else
																			isSet = 0;
																	}
																	else
																		if (typeS == "CHAR")
																		{
																			map<string, multiset<string>>::iterator itSS = mapString.find(nameS);
																			multiset<string>::iterator itss = itSS->second.begin();
																			advance(itss, x);
																			if (itss != itSS->second.end())
																			{
																				itSS->second.erase(*itss);
																				itSS->second.insert(valueSet);
																			}
																			else
																				isSet = 0;
																		}
															}
													if (isSet == 0)
														cout << "Conditioning value does not exist" << endl;
													else
													{
														cout << "Table " << tableName << " has been updated with the column " << columnNameSet << " with the following value:  " << valueSet << " where the column " << nameColumnWhere << " had the value " << valueWhere << endl;
														k.fileBinaryDisplay(tableName, mapInt, mapFloat, mapString);
													}
												}
											}

										}

									}

								}
							}
							break;
						}
						case SELECT:
						{

							result = Select(tableName, input, columns);
							string name = tableName;
							name += ".txt";
							ifstream h(name.c_str());
							if (!h.good())
								cout << "ERROR: file DOES NOT  exist";
							else
							{
								if (result == 2)
								{
									sel++;
									string nameSelect = "SELECT_";
									nameSelect += to_string(sel);
									nameSelect += ".txt";
									ofstream fileSelect;
									fileSelect.open(nameSelect, ios::out);
									cout << "All columns selected " << tableName << endl;
									map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
									map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
									for (list<string>::iterator itC = it1->second.begin(), itT = it2->second.begin(); itC != it1->second.end(), itT != it2->second.end(); itC++, itT++)
									{
										string name = *itC;
										name += ".";
										name += tableName;
										cout << "Columns values " << *itC << endl;
										if (*itT == "INT")
										{
											map < string, multiset<int>>::iterator iter;
											iter = mapInt.find(name);
											for (multiset<int>::iterator iti = iter->second.begin(); iti != iter->second.end(); iti++)
											{
												cout << *iti << " ";
												fileSelect << *iti << " ";
											}
											cout << endl;
											fileSelect << endl;
										}
										else
											if (*itT == "FLOAT")
											{
												map < string, multiset<float>>::iterator iter;
												iter = mapFloat.find(name);
												for (multiset<float>::iterator itf = iter->second.begin(); itf != iter->second.end(); itf++)
												{
													cout << *itf << " ";
													fileSelect << *itf << " ";
												}
												cout << endl;
												fileSelect << endl;
											}
											else
												if (*itT == "CHAR")
												{
													map < string, multiset<string>>::iterator iter;
													iter = mapString.find(name);
													for (multiset<string>::iterator its = iter->second.begin(); its != iter->second.end(); its++)
													{
														cout << *its << " ";
														fileSelect << *its << " ";
													}
													cout << endl;
													fileSelect << endl;
												}

									}
								}
								else
								{
									if (result == 1)
									{
										bool cont = 1;
										map<string, list<string>>::iterator it1 = mapDB_Columns.find(tableName);
										p = strtok(columns, " ");
										while (p != NULL)
										{
											string nameC = "";
											for (int i = 0; i < strlen(p); i++)
												nameC += p[i];
											bool found = 0;
											for (list<string>::iterator it = it1->second.begin(); it != it1->second.end(); it++)
											{
												if (nameC == *it)
												{
													found = 1;
													break;
												}
											}
											if (found == 0)
											{
												cont = 0;
												break;
											}
											p = strtok(NULL, " ");
										}
										if (cont == 0)
											std::cout << "The column does not exist" << endl;
										else
										{

											sel++;
											string nameSelect = "SELECT_";
											nameSelect += to_string(sel);
											nameSelect += ".txt";
											ofstream fileSelect;
											fileSelect.open(nameSelect, ios::out);
											std::cout << "You selected " << columns << "from table " << tableName << endl;
											map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
											char* q;
											q = strtok(columns, " ");
											while (q != NULL)
											{
												string nameC = "";
												for (int i = 0; i < strlen(q); i++)
													nameC += q[i];
												string type;
												//map<string, list<string>>::iterator it2 = mapDB_Type.find(tableName);
												for (list<string>::iterator ic = it1->second.begin(), it = it2->second.begin(); ic != it1->second.end(), it != it2->second.end(); ic++, it++)
													if (*ic == nameC)
														type = *it;
												nameC += ".";
												nameC += tableName;
												if (type == "INT")
												{
													map < string, multiset<int>>::iterator iter;
													iter = mapInt.find(nameC);
													for (multiset<int>::iterator iti = iter->second.begin(); iti != iter->second.end(); iti++)
													{
														cout << *iti << " ";
														fileSelect << *iti << " ";
													}
													cout << endl;
													fileSelect << endl;
													//if (itC == it1->second.begin())
													//	cout << *iti<<" ";
													//else
												}
												else
													if (type == "FLOAT")
													{
														map < string, multiset<float>>::iterator iter;
														iter = mapFloat.find(nameC);
														for (multiset<float>::iterator itf = iter->second.begin(); itf != iter->second.end(); itf++)
														{
															cout << *itf << " ";
															fileSelect << *itf << " ";
														}
														cout << endl;
														fileSelect << endl;
														//if (itC == it1->second.begin())
														//	cout << *itf << " ";
														//else
														//{
														//cout << *itf << " ";
														//itf++;
														//}
													}
													else
														if (type == "CHAR")
														{
															map < string, multiset<string>>::iterator iter;
															iter = mapString.find(nameC);
															for (multiset<string>::iterator its = iter->second.begin(); its != iter->second.end(); its++)
															{
																cout << *its << " ";
																fileSelect << *its << " ";
															}
															cout << endl;
															fileSelect << endl;
															//if (itC == it1->second.begin())
															//	cout << *its << " ";
															//else
															//{
															//	cout << *its << " ";
															//	its++;
															//}
														}
												q = strtok(NULL, " ");
											}
										}
									}
								}
							}
							break;
						}
						case INSERT:
						{
							vector<int> valueTypesList;
							result = Insert(tableName, input, values, valueTypesList);
							if (result)
							{
								string name = tableName;
								name += ".txt";
								fstream h(name.c_str(), ios::in);
								if (!h.good())
									std::cout << "ERROR: file DOES NOT  exist";
								else
								{
									string nameaux = tableName;
									map<string, list<string>>::iterator it = mapDB_Type.find(nameaux);
									std::cout << it->first;
									int noColumnsTable = it->second.size();
									int noValues = valueTypesList.size();
									std::cout << noColumnsTable << " " << noValues << endl;
									if (noColumnsTable != noValues)
										std::cout << "Number of values if different from the number of columns" << endl;
									else
									{
										int val; bool inserted = 1;
										list<string>::iterator itBD = it->second.begin();
										vector<int>::iterator itValues = valueTypesList.begin();
										while (itValues != valueTypesList.end())
										{
											if (*itBD == "INT")
											{
												val = INTEGER_NB;
											}
											else
											{
												if (*itBD == "FLOAT")
													val = FLOAT_NB;
												else
													if (*itBD == "CHAR")
														val = IDENTIFICATOR;
											}
											if (val != *itValues)
											{
												inserted = 0;
												break;
											}
											itBD++; itValues++;
										}
										if (inserted)
										{
											std::cout << "You inserted inside the table " << tableName << " the following values " << values << endl;
											char* p;
											p = strtok(values, " ");

											for (map<string, list<string>>::iterator it1 = mapDB_Columns.begin(), it2 = mapDB_Type.begin(); it1 != mapDB_Columns.end(), it2 != mapDB_Type.end(); it1++, it2++)
											{
												list<string>::iterator itC = it1->second.begin(), itL = it2->second.begin();
												while (p != NULL && itC != it1->second.end() && itL != it2->second.end())
												{
													string name = *itC;
													name += ".";
													name += tableName;

													if (*itL == "INT")
														setInt.insert(atoi(p));
													else
														if (*itL == "FLOAT")
															setFloat.insert(atof(p));
														else
															if (*itL == "CHAR")
															{
																string s = "";
																for (int i = 0; i < strlen(p); i++)
																	s += p[i];
																setString.insert(s);
															}
													itC++; itL++; p = strtok(NULL, " ");

												}
												for (list<string>::iterator itc = it1->second.begin(), itl = it2->second.begin(); itc != it1->second.end(), itl != it2->second.end(); itc++, itl++)
												{
													string name = *itc;
													name += ".";
													name += tableName;
													if (*itl == "INT")
													{
														map<string, multiset<int>>::iterator iter;
														iter = mapInt.find(name);
														if (iter != mapInt.end())
															mapInt.erase(iter);
														mapInt.insert(pair<string, multiset<int>>(name, setInt));
													}
													else
													{
														if (*itl == "FLOAT")
														{
															map<string, multiset<float>>::iterator iter;
															iter = mapFloat.find(name);
															if (iter != mapFloat.end())
																mapFloat.erase(iter);
															mapFloat.insert(pair<string, multiset<float>>(name, setFloat));
														}
														else
															if (*itl == "CHAR")
															{
																map<string, multiset<string>>::iterator iter;
																iter = mapString.find(name);
																if (iter != mapString.end())
																	mapString.erase(iter);
																mapString.insert(pair<string, multiset<string>>(name, setString));
															}
													}
												}
											}
											z.fileBinaryInsert(tableName, values, mapInt, mapFloat, mapString);
										}
										else
											std::cout << "Values inserted do not match the columns" << endl;
									}
								}
							}
							break;
						}
						case IMPORT:
						{
							result = Import(tableName, input, importName);
							if (result)
							{
								string name = tableName;
								name += ".txt";
								ifstream h(name.c_str());
								if (!h.good())
									cout << "ERROR: file DOES NOT  exist";
								else
								{
									string name = importName;
									name += ".csv";
									string af;
									fstream w; bool ok = 1, okk = 1;
									w.open(name, ios::in | ios::binary);
									//while (!w.eof())
									while (!w.eof())
									{
										getline(w, af);
										cout << af << endl;// << " " << af.find(',') << "//";
										char* o;
										o = strtok((char*)af.c_str(), " ");
										while (o != NULL)
										{
											if (o[strlen(o) - 1] == ',')
											{
												cout << o << " " << o[strlen(o) - 1] << endl;
												o = strtok(NULL, " ");
											}
											else
											{
												// cout << "another found";
												ok = 0;
												break;
											}
										}
										cout << o << endl;
										string aff;
										aff = af.substr(af.length() - 1);
										cout << aff << aff.c_str() << endl;

										if (ok == 0)
											if (strcmp(o, aff.c_str()))
											{
												okk = 0;
												cout << "another";
											}
											else
												cout << "success";
									}
									k.importCSV(tableName, importName, existed);
									if (okk == 0)
										cout << "Not using the right separator";
									else
									{
										cout << "Table imported: " << tableName << endl << " Values from the CSV file: " << importName << endl;


									}
								}
							}
							break;
						}
						default:
						{
							cout << "ERROR: illegal command\n";
							break;
						}
						}
						//strcpy(input, input + 2);
						commandType(input, &tokenType);
						if (tokenType == ';')
						{
							moreCommands = 1;
						}
					} while (tokenType == ';');
				}
			}

		}
		else
		{
			if (argc >= 2 && argc <= 6)
			{
				bool txt = 1;
				for (int i = 1; i < argc; i++)
				{
					if (strstr(argv[i], ".txt") == NULL)
					{
						cout << "ERROR: not all text files";
						txt = 0;
						break;
					}
				}
				if (txt)
				{
					for (int i = 1; i < argc; i++)
					{
						ifstream h(argv[i]);
						if (!h.good())
							cout << "ERROR: file DOES NOT  exist, so it cannot be used as an argument";
						else
						{
							hCommands.fileTextRead(argc, argv, i);
						}
					}
				}
			}
		}
	}
}