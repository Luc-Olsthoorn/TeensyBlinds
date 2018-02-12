//Ascii art time
//----A0----
//F5------B1
//----G6----
//E4------C2
//----D3----
//-------DP7
//pin->position
//1->4 
//2->3

//4->2
//5->7
//6->1
//7->0

//9->5
//10->6
class LEDSegment{
	private:
		int LEDSegmentArray[8];
		int led[8][8]={{0,0,0,1,0,1,0,1},{1,0,0,1,1,1,1,1},{0,0,1,0,0,1,0,1},{0,0,0,0,1,1,0,1},{1,0,0,1,1,0,0,1},{0,1,0,0,1,0,0,1}};
		int last;
	public:
		//store array
		LEDSegment(int arr[]){
			 for (int i =0; i<8; i++){
			 	LEDSegmentArray[i] = arr[i];
			 }
		}
		//initialize pins
		void setup(){
			for(int i=0; i < 8; i++){
				pinMode(LEDSegmentArray[i], OUTPUT);
			}		
		}
		void turnOff(){
			for(int i =0; i<8; i++){
				digitalWrite(LEDSegmentArray[i], HIGH);
			}
			last = 9;
		}
		void change(int in){
			for(int i =0; i<8; i++){
				digitalWrite(LEDSegmentArray[i], led[in][i]);
			}
		}
		void changeNum(int num){
			if(last != num){
				change(num);
			}
			last = num;
			
		}
};