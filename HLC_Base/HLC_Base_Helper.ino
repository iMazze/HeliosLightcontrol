// Handles the Serial input from the HLC_Web
void handleSerialRecieve()
{
    Serial.print("Rcieved from HLC_Web: ");
    Serial.println(buf);
    if(StrContains(buf, "matrix_OFF") || StrContains(buf, "matrix_fft_OFF") || StrContains(buf, "matrix_temperaturverlauf_OFF") || StrContains(buf, "matrix_beleuchtungNachTemperatur_OFF"))
    {
        matrixMode = off;
    }
    else if(StrContains(buf, "matrix_fft_ON"))
    {
      matrixMode = fft;
    }
    else if(StrContains(buf, "matrix_temperaturverlauf_ON"))
    {
        matrixMode = temperaturverlauf;
    }
    else if(StrContains(buf, "matrix_beleuchtungNachTemperatur_ON"))
    {
        matrixMode = beleuchtungNachTemperatur;
    }
    else if(StrContains(buf, "lamp_ON"))
    {
        lampOn = true;
    }
    else if(StrContains(buf, "lamp_OFF"))
    {
        lampOn = false;
    }
}

// Reads one line from the buffer
int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\r': // Ignore CR
                break;
            case '\n': // Return on new-line
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}
