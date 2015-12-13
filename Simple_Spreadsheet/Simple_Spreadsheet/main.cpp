/*
Programming Finance Final Project
Written by Ankit Shah
*/

#include<iostream>
#include<string>
#include"cell.h"
#include<exception>
#include<sstream>
std::string line;

int col = 0;
int row = 0;

int main(int argc, char** argv){

	//Check if the user has provided the proper value of height and width of the spreadsheet
	if (argc != 3){
		std::cout << "Enter only two arguments";
		return 1;
	}
	try{
		col = std::stoi(std::string(argv[1]));       //Converts the argument into an integer value for columns
		row = std::stoi(std::string(argv[2]));       //Converts the argument into an integer value for rows

		//Checks that the user doesn't provide negative values of rows or columns
		if (col <= 0 || row <= 0){
			std::cout << "Rows or columns cannot be negative";
			return 1;
		}
		//Creates a two dimensional Linked List
		LList<LList<Cell*>> rows;
		//The height is the number of rows
		for (int i = 0; i < row; ++i) {
			LList<Cell*> empty;
			rows.push_back(empty);
			//Make a new empty cell in this row for every column
			for (int j = 0; j < col; ++j) {
				//The back() operator returns a reference to the last element in the list
				rows.back().push_back(new Cell());

			}
		}

		std::string line;

		//Loop for performing various spreadsheet operations until the user quits
		while (std::getline(std::cin, line)) {
			// Convert the string into an input stream and read in the command
			std::istringstream ss(line);
			std::string command;
			ss >> command;

			//Command to print the spreadsheet 
			if (command == "print"){

				//Loop for printing the sheet
				for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); I++){
					for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){
						if ((*J) != (*I).back()){                //Condition to avoid printing comma after printing the last cell
							std::cout << (*J)->toString() << ",";
						}
						else{
							std::cout << (*J)->toString();      //Function to print the cell
						}
					}
					std::cout << "\n";

				}
			}

			//Quit using the spreadsheet when the user gives a quit command
			else if (command == "quit"){
				for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); I++){
					for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){
						delete *J;
						std::cout << "\nThe value of count is:" << Cell::c;
					}
				}
				return 0;
			}

			//Command to set the value of different cells in spreadsheet
			else if (command == "set"){

				std::string c, r;
				ss >> c >> r;
				try{

					int co = (std::stoi(std::string(c))) + 1;
					int ro = (std::stoi(std::string(r))) + 1;

					//Checks that the user doesn't provide negative values of rows or columns
					if (co < 0 || ro < 0){
						std::cout << "Rows or columns cannot be negative";
						return 1;

					}

					//Checks that the user doesn't provide the location of the cell beyond the spreadsheet 
					if (col < co || row < ro){
						std::cout << "Error: cell out of range\n";

					}
					std::string s;
					ss >> s;
					if (s == "number"){
						try{
							std::string n;
							ss >> n;
							double num = std::stod(std::string(n)); //Number to be inserted into the numeric cell

							int h = 0, w = 0;
							//Loop to iterate to the given location
							for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); I++){
								h++;
								w = 0;
								for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){
									w++;
									if (h == ro && w == co){
										delete *J;                       //Deletes the earlier cell
										*J = new NumericCell(num);       //Creates a new Numeric cell at the given location 


									}
								}
							}
							int hi = 0, wi = 0;

							//This loop is used to update the content of dependent cells
							for (LList<LList<Cell*>>::iterator A = rows.begin(); A != rows.end(); A++){
								hi++;
								wi = 0;
								for (LList<Cell*>::iterator B = (*A).begin(); B != (*A).end(); B++){
									wi++;
									FunctionCell* n;
									n = dynamic_cast<FunctionCell*> (*B);   //Check if its a functioncell
									if (n != NULL){
										(dynamic_cast<FunctionCell*> (*B))->MMM(&rows); //Call the operation performed
									}
								}
							}
						}
						//Catch block for checking whether the user provided correct input for number to be set in the cell
						catch (std::exception e){

							std::cout << "Error: Bad input for set number\n";
						}
					}
					//Checks if the user wants to set the value of a cell as a string
					else if (s == "string"){

						int h = 0, w = 0;
						std::string ipstr;              //Declaration for input string to be inserted in the string cell
						std::getline(ss, ipstr);        //Saves the string to be set into input string
						if (ipstr[0] < 33){
							ipstr.erase(ipstr.begin()); //removes all leading whitespace
						}
						else if (ipstr[ipstr.size() - 1] < 33){
							ipstr.erase(ipstr.size() - 1); //removes all trailing whitespace
						}

						//Loop to iterate to the given location
						for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); I++){
							h++;
							w = 0;
							for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); J++){
								w++;
								if (h == ro && w == co){
									//Checks whether the user entered the string to be put in the cell
									if (ipstr.empty()) {
										std::cout << "No input string detected\n";
									}
									else{
										delete *J;                   //Deletes the earlier cell
										*J = new StringCell(ipstr);  //Creates a new String cell at the given location 
									}
								}
							}
						}

					}
					//Checks if the user wants to set the value of a cell as a mean of a range of rows
					else if (s == "mean"){

						try{

							std::string row_m, of1, of2;
							ss >> row_m;                 //String input for row number
							ss >> of1;                   //String input for the first offset
							ss >> of2;                   //String input for the second offset

							//Convert the string inputs to integers
							int row_num = std::stoi(std::string(row_m));
							int offset1 = std::stoi(std::string(of1));
							int offset2 = std::stoi(std::string(of2));

							//Function to passs all the values into the Function cell
							FunctionCell(co, ro, row_num, offset1, offset2, s, &rows);
						}
						catch (std::exception e){
							//Catches errors in function cell parameters due to stoi
							std::cout << "Error: function incorrect\n";
						}

					}
					//Checks if the user wants to set the value of a cell as a max of a range of rows
					else if (s == "max"){

						try{

							std::string row_m, of1, of2;
							ss >> row_m;                    //String input for row number
							ss >> of1;                      //String input for the first offset 
							ss >> of2;                      //String input for the second offset

							//Convert the string inputs to integers
							int row_num = std::stoi(std::string(row_m));
							int offset1 = std::stoi(std::string(of1));
							int offset2 = std::stoi(std::string(of2));

							//Function to passs all the values into the Function cell
							FunctionCell(co, ro, row_num, offset1, offset2, s, &rows);


						}
						catch (std::exception e){
							//Catches errors in function cell parameters due to stoi
							std::cout << "Error: function incorrect\n";
						}

					}
					//Checks if the user wants to set the value of a cell as a min of a range of rows
					else if (s == "min"){

						try{

							std::string row_m, of1, of2;
							ss >> row_m;                 //String input for row number  
							ss >> of1;                   //String input for the first offset
							ss >> of2;                   //String input for the second offset

							//Convert the string inputs to integers
							int row_num = std::stoi(std::string(row_m));
							int offset1 = std::stoi(std::string(of1));
							int offset2 = std::stoi(std::string(of2));

							//Function to passs all the values into the Function cell
							FunctionCell(co, ro, row_num, offset1, offset2, s, &rows);
						}
						catch (std::exception e){
							//Catches errors in function cell parameters due to stoi
							std::cout << "Error: function incorrect\n";
						}


					}

					for (LList<LList<Cell*>>::iterator A = rows.begin(); A != rows.end(); A++){

						for (LList<Cell*>::iterator B = (*A).begin(); B != (*A).end(); B++){

							FunctionCell* n;
							n = dynamic_cast<FunctionCell*> (*B);
							if (n != NULL){
								(dynamic_cast<FunctionCell*> (*B))->MMM(&rows);
							}
						}
					}

				}
				catch (std::exception e){
					//Catch block for checking whether the user provided correct input for number to be set in the cell
					std::cout << "Error : Bad input for set number\n";
				}

			}
			//Command to add the row before the given row
			else if (command == "addrow"){

				std::string add;
				ss >> add;
				try{
					int addrow = std::stoi(std::string(add));

					//Loop to add the row before the given row
					if (addrow >= 0 && addrow <= row){
							{
								LList<LList<Cell*>>::iterator I = rows.begin();
								for (int i = 0; i != addrow; i++){
									I++;
								}
								LList<Cell*> empty;
								LList<LList<Cell*>>::iterator J = rows.begin();
								J = rows.insert(I, empty, addrow);
								for (int i = 0; i < col; i++){         /*Inserts a new row of cells before the desired location*/
									(*J).push_back(new Cell());
								}
							}
						++row;                //Increments the number of  rows after the row is added
					}
					//Checks if the row number given by the user is in range
					else{
						std::cout << "Error: row out of range\n";
					}
				}
				//Checks if the row number given by the user is in range
				catch (std::exception e){
					std::cout << "Error: row out of range\n";
				}


			}
			else if (command == "removerow"){

				std::string del;
				ss >> del;
				try{
					int delrow = std::stoi(std::string(del));
					//Loop to delete the given row
					if (delrow >= 0 && delrow <= row){
							{
								LList<LList<Cell*>>::iterator I = rows.begin();
								for (int i = 0; i != delrow; i++){
									I++;
								}
								LList<Cell*> empty;
								LList<LList<Cell*>>::iterator J = rows.begin();
								J = rows.erase(I, delrow);

							}
						--row;           //Decrements the number of rows after the given row is deleted
					}
					//Checks if the row number given by the user is in range
					else{
						std::cout << "Error: row out of range\n";
					}
				}
				//Checks if the row number given by the user is in range
				catch (std::exception e){
					std::cout << "Error: row out of range\n";
				}


			}
			//Checks if the user has provided proper commands
			else{
				std::cout << "Error: unknown command\n";
			}
		}
	}

	catch (std::exception e){
		// Handles the failure of the stoi function
		std::cout << " Got bad values for width and height !\n";
		return 1;
	}




}