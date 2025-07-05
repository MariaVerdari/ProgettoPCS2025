#include <gtest/gtest.h>

#include "test.hpp"


	bool q3 = false;
	bool q4 = false;
	bool q5 = false;
	bool p4 = false;
	bool p5 = false;
	int b;
	int c;
	
int main(int argc, char *argv[])
{


	if (argc == 5 || argc == 7){
		int quadrupla[4];
		for (unsigned int i = 0; i < 4; i++) { //mi assicuro che tutti gli interi siano validi
			istringstream convert(argv[i+1]);
			if (!(convert >> quadrupla[i])  || !(convert.eof())) { //no numeri con il punto
				cerr << "Errore: l'argomento '" << argv[i + 1] << "' non è un intero valido"<<endl;
				return 1;
			}
		}
		int p = quadrupla[0];
		int q = quadrupla[1];
		b = quadrupla[2];
		c = quadrupla[3];
		
		if (b== 0){
			b = c;
			c=0;
		}
		
		
		
		if (b==c){ // seconda classe
		cout<< "seconda classe b = c"<<endl;
		
			
			if (p == 3){
				
				switch(q) {
					case 3: //tetraedro
						
						break;
													
						
	
	
					case 4: //ottaedro
						
						break;

						
	
					

					case 5: //icosaedro
						
						break;
					
					default:
					cerr << "Errore: l'argomento "<< q <<" non è valido: q può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
			

				
				
			
			} else if (q ==3) // duale seconda classe
			{
				switch(p){
					
					case 4: //ottaedro
				

					break;
						
	
					

					case 5: //icosaedro
					
					break;
					
					default:
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
				
											
				
							
			} else { //nessuno dei due casi
			cerr << "Errore: nessuno degli argomenti p e q è pari a 3"<<endl;
			return 1;
				
			}

		
			
		}
		else if (b == 0 || c == 0) { // prima classe
		
		
			
			if (p == 3){
				
				switch(q) {
					case 3: //tetraedro
						q3 = true;
						break;
													
					case 4: //ottaedro
						q4 = true;
						break;

					case 5: //icosaedro
    					q5 = true;
						break;
					
					default:
					cerr << "Errore: l'argomento "<< q <<" non è valido: q può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
					
			
			} else if (q ==3) // duale
			{ 
				switch(p){
					
					case 4: //ottaedro
						p4 = true;
						break;
					break;
						
					case 5: //icosaedro
						p5 = true;
						break;
					break;
					
					default:
					cerr << "Errore: l'argomento "<< p <<" non è valido: p può assumere solo i valori 3, 4 e 5"<<endl;
					return 1;
					
				}
				
				
				
			} else { //nessuno dei due casi
			cerr << "Errore: nessuno degli argomenti p e q è pari a 3"<<endl;
			return 1;
				
			}
			
		
		
		
		}
		else {// nessuno dei due casi
			cerr << "Errore: gli argomenti "<< b <<" e "<< c<<", ovvero b e c, sono diversi tra loro e nessuno dei due è pari a 0"<<endl;
			return 1;
		}

	
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
	
		
	}

	else{
		cerr << "Errore: l'input può essere una quadrupla oppure una sestupla di numeri interi"<<endl;
		return(1);
	}
		
	
	

}
