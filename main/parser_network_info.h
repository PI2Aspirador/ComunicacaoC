#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* get_ip(char* string);
char** str_split(char* a_str, const char a_delim);
char* get_rssi(char* string);

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


char* get_rssi(String string){
  char** token;
  char* result; 
  char * string_convert;
  int i=0;
  int achei =0;
  Serial.println("EITA PORRA");
  string.toCharArray(string_convert, sizeof(string));
  Serial.println(string_convert);

  Serial.println("Vamos ver..");
  Serial.println(string_convert);
  token = str_split(string_convert, ',');

  if (token){
    Serial.println("FOOOI");
    int i;
    for (i = 0; *(token + i); i++){//Ele não ta entrando nesse for, o token ta com nulo. A string convertida ta nula.. então seus tokens também. Retirar tipo String.
      Serial.print("Token=[");
      Serial.print(*(token + i));
      Serial.println("]");
      free(*(token + i));
    }
    printf("\n");
    free(token);
  }

    
    strcat(result, "\0"); 
    Serial.print("Olha: ");
    Serial.println(result);
    //result = &result[1];

    Serial.println(result);
    return result;
    
}

char* get_ip(char * string){
  char** tokens;
  char* result; 
  tokens = str_split(string, '"');

  if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
            if(i=1){
              result = *(tokens + i);
              break;
            }
        }
        free(tokens);
    } 

    return result;
}


