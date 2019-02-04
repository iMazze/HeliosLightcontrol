
void setup()
{
    
};

void timer_loop() 
{
    // alle 500ms
    if(!(counter % 10))
    {
        d.toggleLed();
    } 
    // alle 1s
    else if(!(counter % 20))
    {
        
    }

    // increment counter
    counter++;
}
 

void loop(){
    
};
