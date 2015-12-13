#include<iostream>
#include<string>
#include <limits>
#include"cell.h"

unsigned Cell::c = 0;
std::string Cell::toString(){

	return "";
}

NumericCell::NumericCell(){};                 //Default constructor for NumericCell

NumericCell::NumericCell(double v){

	val = v;

}
std::string NumericCell::toString(){

	return std::to_string(val);

}
double NumericCell::getValue(){
	return val;
}
StringCell::StringCell(std::string s){

	str = s;
}
std::string StringCell::toString(){

	return str;
}
std::string FunctionCell::toString(){

	return std::to_string(value);

}
FunctionCell::FunctionCell(int c, int r, int row_ip, int of1, int of2, std::string type, LList<LList<Cell*>>(*sheet)) :NumericCell(){
	col = c;
	row = r;
	op = type;
	rows = row_ip;
	offset_1 = of1;
	offset_2 = of2;
	pass = sheet;
	MMM(pass);

}
FunctionCell::FunctionCell(double v, int c, int r, int row_ip, int of1, int of2, std::string type) :NumericCell(v){
	value = v;
	col = c;
	row = r;
	op = type;
	rows = row_ip;
	offset_1 = of1;
	offset_2 = of2;


}
FunctionCell::FunctionCell(double v) :NumericCell(v){
	value = v;
}

void FunctionCell::MMM(LList<LList<Cell*>>(*pass)){


	for (LList<LList<Cell*>>::iterator I = pass->begin(); I != pass->end(); I++){

		for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){

			//Checks for the required row and offset1
			if (h == rows && w == offset_1){
				//Checks if the user wants the mean
				if (op == "mean"){
					//Loop to iterate through the row
					for (int i = offset_1; i <= offset_2; ++i){
						//Checks if the cell is a numeric cell and ignores the stringcell
						if (dynamic_cast<NumericCell*> (*J) != NULL) {
							sum += dynamic_cast<NumericCell*> (*J)->getValue();
							++n;
							++J;   //Points to the next cell
							++a;   //Counter to check if atleast one numeric cell is preset

						}


					}
					//Shows an error if there are no numeric cells
					if (a == 0){
						std::cout << "not a number\n";

					}

					mean = sum / n;



				}
				//Checks if the user wants the max
				else if (op == "max"){
					//Loop to iterate through the row
					for (int i = offset_1; i <= offset_2; ++i){
						//Checks if the cell is a numeric cell and ignores the stringcell
						if (dynamic_cast<NumericCell*> (*J) != NULL) {
							maxh = dynamic_cast<NumericCell*> (*J)->getValue();
							++J;        //Points to the next cell
							++a;        //Counter to check if atleast one numeric cell is preset
							//Logic to find the max
							if (maxh > max){
								max = maxh;
							}
						}


					}
					//Shows an error if there are no numeric cells
					if (a == 0){
						std::cout << "not a number\n";

					}

				}
				//Checks if the user wants the max
				else if (op == "min"){
					//Loop to iterate through the row
					for (int i = offset_1; i <= offset_2; ++i){
						if (dynamic_cast<NumericCell*> (*J) != NULL) {
							minh = dynamic_cast<NumericCell*> (*J)->getValue();
							++J;         //Points to the next cell
							++a;         //Counter to check if atleast one numeric cell is preset
							//Logic to find the min
							if (i == offset_1){
								min = minh;
							}
							else if (minh < min){
								min = minh;
							}
						}


					}
					//Shows an error if there are no numeric cells
					if (a == 0){
						std::cout << "not a number\n";

					}

				}
			}
			w++;
		}
		h++;
		w = 0;
	}


	//Loop to change the value of the user defined cell
	int he = 0, wi = 0;
	for (LList<LList<Cell*>>::iterator I = pass->begin(); I != pass->end(); I++){
		he++;
		wi = 0;
		for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){
			wi++;

			if (he == row && wi == col){
				if (op == "mean"){
					if (a != 0){
						delete *J;
						*J = new FunctionCell(mean, col, row, rows, offset_1, offset_2, op);
					}
					else{
						double m = std::numeric_limits < double >::quiet_NaN();
						delete *J;
						*J = new FunctionCell(m);
					}
				}
				else if (op == "max"){
					if (a != 0){
						delete *J;
						*J = new FunctionCell(max, col, row, rows, offset_1, offset_2, op);
					}
					else{
						double m = std::numeric_limits < double >::quiet_NaN();
						delete *J;
						*J = new FunctionCell(m);
					}
				}
				else if (op == "min"){
					if (a != 0){
						delete *J;
						*J = new FunctionCell(min, col, row, rows, offset_1, offset_2, op);
					}
					else{
						double m = std::numeric_limits < double >::quiet_NaN();
						delete *J;
						*J = new FunctionCell(m);
					}


				}
			}

		}
	}
}
