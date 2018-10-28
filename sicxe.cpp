#include<iostream>
#include<fstream>
#include<string>
#include<iterator>
#include<algorithm>
#include<sstream>
using namespace std;
int LOCCTR=0;
int STARTADRESS=0;
string SYMTAB[100][2];
int symtabsz=0;
int error=0;
int optabsz=101;
int PGMLENGTH;
string OPTAB[][3]={
	{"ADD","18","3"},
	{"ADDF","58","3"},
	{"ADDR","90","2"},
	{"AND","40","3"},
	{"CLEAR","B4","2"},
	{"COMP","28","3"},
	{"COMPF","88","3"},
	{"COMPR","A0","2"},
	{"DIV","24","3"},
	{"DIVF","64","3"},
	{"DIVR","9C","2"},
	{"FIX","C4","1"},
	{"FLOAT","C0","1"},
	{"HIO","F4","1"},
	{"J","3C","3"},
	{"JEQ","30","3"},
	{"JGT","34","3"},
	{"JLT","38","3"},
	{"JSUB","48","3"},
	{"LDA","00","3"},
	{"LDB","68","3"},
	{"LDCH","50","3"},
	{"LDF","70","3"},
	{"LDL","08","3"},
	{"LDS","6C","3"},
	{"LDT","74","3"},
	{"LDX","04","3"},
	{"LPS","D0","3"},
	{"MUL","20","3"},
	{"MULF","60","3"},
	{"MULR","98","2"},
	{"NORM","C8","1"},
	{"OR","44","3"},
	{"RD","D8","3"},
	{"RMO","AC","2"},
	{"RSUB","4C","3"},
	{"SHIFTL","A4","2"},
	{"SHIFTR","A8","2"},
	{"SIO","F0","1"},
	{"SSK","EC","3"},
	{"STA","0C","3"},
	{"STB","78","3"},
	{"STCH","54","3"},
	{"STF","80","3"},
	{"STI","D4","3"},
	{"STL","14","3"},
	{"STS","7C","3"},
	{"STSW","E8","3"},
	{"STT","84","3"},
	{"STX","10","3"},
	{"SUB","1C","3"},
	{"SUBF","5C","3"},
	{"SVC","B0","2"},
	{"SUBR","94","2"},
	{"TD","E0","3"},
	{"TIO","F8","1"},
	{"TIX","2C","3"},
	{"TIXR","B8","2"},
	{"WD","DC","3"},
	


	{"+ADD","18","4"},
        {"+ADDF","58","4"},
       
        {"+AND","40","4"},
        
        {"+COMP","28","4"},
        {"+COMPF","88","4"},
        
        {"+DIV","24","4"},
        {"+DIVF","64","4"},
        
        
       
        
        {"+J","3C","4"},
        {"+JEQ","30","4"},
        {"+JGT","34","4"},
        {"+JLT","38","4"},
        {"+JSUB","48","4"},
        {"+LDA","00","4"},
        {"+LDB","68","4"},
        {"+LDCH","50","4"},
        {"+LDF","70","4"},
        {"+LDL","08","4"},
        {"+LDS","6C","4"},
        {"+LDT","74","4"},
        {"+LDX","04","4"},
	{"+LPS","D0","4"},
        {"+MUL","20","4"},
        {"+MULF","60","4"},
     
        
        {"+OR","44","4"},
        {"+RD","D8","4"},
        
        {"+RSUB","4C","4"},
        
        
     
        {"+SSK","EC","4"},
        {"+STA","0C","4"},
        {"+STB","78","4"},
        {"+STCH","54","4"},
        {"+STF","80","4"},
        {"+STI","D4","4"},
        {"+STL","14","4"},
        {"+STS","7C","4"},
        {"+STSW","E8","4"},
        {"+STT","84","4"},
        {"+STX","10","4"},
        {"+SUB","1C","4"},
        {"+SUBF","5C","4"},
       
       
        {"+TD","E0","4"},
       
        {"+TIX","2C","4"},
        
        {"+WD","DC","4"}


	};
string PGBLOCK[100][4];
int BLOCK_NO=0;

int block_sz=1;
int search_symtab(string label){
	for(int i=0;i<symtabsz;i++){
		if(SYMTAB[i][0].compare(label)==0)
			return 1;
	}
	return 0;
}
void insert_to_symtab(string label,int locctr){
	SYMTAB[symtabsz][0]=label;
	stringstream ss;
	ss<< hex << locctr; // int decimal_value
	string res ( ss.str() );

	SYMTAB[symtabsz][1]=res;
	symtabsz++;
}

int find_length(string operand){
	if(operand.at(0)=='C'){
		return operand.length()-3;   //check here for syntax
	}
	if(operand.at(0)=='X'){
		return (operand.length()-3)/2; //check here for syntax and size

	}
	if(operand.at(0)=='='){
		if(operand.at(1)=='C'){
			return operand.length()-4;
		}
		else
			return (operand.length()-4)/2;
	}
	return 0;
}
int search_optab(string opcode){
	for(int i=0;i<optabsz;i++){
		if(OPTAB[i][0].compare(opcode)==0)
			return i;
	}
	return -1;
}
int search_block(string operand){
	for(int i=0;i<block_sz;i++){
		if(PGBLOCK[i][0].compare(operand)==0)
			return i;
	}
	return -1;
}
void update_block_table(){

	for(int i=0;i<block_sz-1;i++){
		//cout<<"before"<<i;
		stringstream no1(PGBLOCK[i][2]);
		stringstream no2(PGBLOCK[i][3]);
		int nno1,nno2;
		no1>>nno1;
		no2>>nno2;
		//cout<<"\n"<<nno1;
		//cout<<"\n"<<nno2;


		//stringstream res;
		//res<<(nno1+nno2);
		//cout<<"before"<<i;
		nno1=nno1+nno2;
		//cout<<"before"<<i;
		PGBLOCK[i+1][2]=to_string(nno1);
		//cout<<"after"<<i;
		//cout<<"block size:"<<block_sz;
		
	}
}



int pass1(int lineno,string label,string opcode,string operand,char argv[]){
	fstream intermediate;
	string str(argv);
	intermediate.open((str+"_intermediate.txt"),ios::app);
	
	if(opcode.compare("START")==0){
			stringstream no(operand);
			no>>STARTADRESS;
			LOCCTR=STARTADRESS;
			stringstream ss2;
			ss2<<hex << LOCCTR; 
			string res ( ss2.str() );
			//stringstream res2;
			//res2<<BLOCK_NO;

			intermediate<<to_string(BLOCK_NO)<<"\t"<<res<<"\t"<<opcode<<"\t"<<operand<<"\n";
			intermediate.close();

			return 1;
	}
	if(opcode.compare("END")!=0){



	if(opcode.compare("USE")==0){
		if(operand.compare("")==0){
			stringstream nn(PGBLOCK[0][3]);
			int lct;
			nn>>lct;
		//	cout<<"lct"<<PGBLOCK[0][3];
			LOCCTR=lct;
			BLOCK_NO=0;
		}
	
		else{
			int stat_b=search_block(operand);
			if(stat_b>=0){
				BLOCK_NO=stat_b;
				stringstream nn2(PGBLOCK[stat_b][3]);
				nn2>>LOCCTR;
				//LOCCTR=PGBLOCK[stat_b][2];
			}
			else{
				block_sz++;
				BLOCK_NO=block_sz-1;
				PGBLOCK[block_sz-1][0]=operand;
				PGBLOCK[block_sz-1][1]=to_string(block_sz-1);
				stringstream no1(PGBLOCK[block_sz-2][2]);
				stringstream no2(PGBLOCK[block_sz-2][3]);
				int nn1,nn2;
				no1>>nn1;
				no2>>nn2;
				//stringstream res;
				//res<<(nn1+nn2);
				PGBLOCK[block_sz-1][2]=to_string(nn1+nn2);
				PGBLOCK[block_sz-1][3]="0";
				LOCCTR=0;
			}
		}
	}




	int temp=LOCCTR;
	if(label.compare("")!=0){
		int stat=search_symtab(label);
		if(stat==1)
			error=1;
		else
			insert_to_symtab(label,LOCCTR);
	}
	int stat2=search_optab(opcode);
	if(stat2>=0){
		stringstream no(OPTAB[stat2][2]);
		int sz;
		no>>sz;
		LOCCTR+=sz;
	}
	else if(opcode.compare("WORD")==0){
			LOCCTR+=3;
	}
	else if(opcode.compare("RESW")==0){
		stringstream no(operand);
		int op;
		no>>op;
		LOCCTR+=3*op;
	}
	else if(opcode.compare("RESB")==0){
		stringstream no(operand);
		int op;
		no>>op;
		LOCCTR+=op;
	}
	else if(opcode.compare("BYTE")==0){
		LOCCTR+=find_length(operand);
	}
	else if(opcode.at(0)=='=')
		LOCCTR+=find_length(opcode);
	else
		error=2;
	PGBLOCK[BLOCK_NO][3]=to_string(LOCCTR);
	
	std::stringstream ss3;
	ss3<< hex << temp; 
	string res ( ss3.str() );


	intermediate<<BLOCK_NO<<"\t"<<res<<"\t"<<opcode<<"\t"<<operand<<"\n";
	intermediate.close();
	return 1;
	}
	stringstream ss4;
	ss4<< hex << LOCCTR; 
	string res ( ss4.str() );

	intermediate<<BLOCK_NO<<"\t"<<res<<"\t"<<opcode<<"\t"<<operand<<"\n";
	PGMLENGTH=LOCCTR-STARTADRESS;
	stringstream ss5;
	ss5<< hex << PGMLENGTH; 
	string res_pgmlength ( ss5.str() );
	cout<<"\n program length"<<res_pgmlength<<endl;
	
	intermediate.close();
	return 0;
}






int main(int argc,char *argv[]){
	

	fstream source;
	string line,label,opcode,operand;
	int lineno=0;
	source.open(argv[1],ios::in);
	PGBLOCK[0][0]="default";
        PGBLOCK[0][1]="0";
        PGBLOCK[0][2]="0";
        PGBLOCK[0][3]="0";
	
	if(source.is_open())
	{       

		while (getline(source, line))
		{	lineno++;
			cout<<"line no"<<lineno;
			cout<<line<<endl;
			if(line.at(0)=='.')
				continue;
    			stringstream ss(line);
    	
    			if(ss >> label >> opcode >> operand)
    			{
				;
		
			}
			else{
				source.seekg(-1*line.length(),ios::cur);
				getline(source,line);
				stringstream ss(line);
				opcode="";operand="";
				ss>>opcode>>operand;
				label="";
					//cout<<"here";
				
				//else{
				/*	cout<<"here"<<endl<<endl;
					source.seekg(-1*(line.length()),ios::cur);
					getline(source,line);
					stringstream ss2(line);
					ss2>>opcode
						label="";operand="";
					*/

				//}

			}
			cout<<"label:"<<label<<"opcode:"<<opcode<<"operand:"<<operand<<endl;
			int p=pass1(lineno,label,opcode,operand,argv[1]);
			if(p==0){update_block_table(); break;}
		//	cout<<"hello";
			//for(int i=0;i<block_sz;i++)
                        //	cout<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<endl;

			update_block_table();
			

    		
		}

		source.close();
		
		
	}
	else cout<<"unable to open source file";
	return 0;
}

