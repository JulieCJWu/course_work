/** 
 * countries.c
 *
 * @author Michael Tessier
 * @version 1.01.00
 * @since 2016-11-16
 */

#include "countries.h"

bool countriesFetchFromJson(struct countryArray *countryArray) {

    int i, j;

    json_t *jsonArray;
    json_error_t error;

    FILE *jsonFile;
    
    jsonFile = fopen("./data/countries/countries.json", "r");
    fseek(jsonFile, 0, SEEK_SET);

    jsonArray = json_loadf(jsonFile, 0, &error);
    fclose(jsonFile);

    if(!jsonArray) {
        printf("error: on line %d: %s\n", error.line, error.text);
        return false;
    }

    if(!json_is_array(jsonArray)) {
        printf("error: jsonArray is not an array\n");
        json_decref(jsonArray);
        return false;
    }

    for(i = 0; i < (int)json_array_size(jsonArray); i++) {
            
            json_t *data, *name, *common_name, *cca3, *capital, *region, *languages, *borders, *buffer;
            void *iter;
            struct stringArray slanguages, sborders;
            stringArrayInit(&slanguages);
            stringArrayInit(&sborders);
            
            data = json_array_get(jsonArray, i);

            if(!json_is_object(data)) {
                printf("error: commit data %d is not an object\n", i+1);
                json_decref(jsonArray);
                return false;
            }

            name = json_object_get(data, "name");
            if(!json_is_object(name)) {
                printf("error: commit %d: name is not an object\n", i+1);
                json_decref(jsonArray);
                return false;
            }

            common_name = json_object_get(name, "common");
            if(!json_is_string(common_name)) {
                printf("error: commit %d: common is not a string\n", i+1);
                json_decref(jsonArray);
                return false;
            }


            cca3 = json_object_get(data, "cca3");
            if(!json_is_string(cca3)) {
                printf("error: commit %d: cca3 is not a string\n", i+1);
                json_decref(jsonArray);
                return false;
            }
            
            capital = json_object_get(data, "capital");
            if(!json_is_string(capital)) {
                printf("error: commit %d: capital is not a string\n", i+1);
                json_decref(jsonArray);
                return false;
            }

            region = json_object_get(data, "region");
            if(!json_is_string(region)) {
                printf("error: commit %d: region is not a string\n", i+1);
                json_decref(jsonArray);
                return false;
            }

            languages = json_object_get(data, "languages");
            if(!json_is_object(languages)) {
                printf("error: commit %d: languages is not an object\n", i+1);
                json_decref(jsonArray);
                return false;
            }
            
            borders = json_object_get(data, "borders");
            if(!json_is_array(borders)) {
                printf("error: commit %d: borders is not an array\n", i+1);
                json_decref(jsonArray);
                return false;
            }
            
            strncpy(countryArray->countries[i].name, json_string_value(common_name), 
                    strlen(json_string_value(common_name))+1);
            strncpy(countryArray->countries[i].code, json_string_value(cca3), 
                    strlen(json_string_value(cca3))+1);
            strncpy(countryArray->countries[i].capital, json_string_value(capital), 
                    strlen(json_string_value(capital))+1);
            strncpy(countryArray->countries[i].region, json_string_value(region), 
                    strlen(json_string_value(region))+1);
            

            

            iter = json_object_iter(languages);
            for(j = 0; j < (int)json_object_size(languages); j++) {
                buffer = json_object_iter_value(iter);

                
                if(!json_is_string(buffer)) {
                printf("error: commit %d: languages buffer is not a string\n", i+1);
                json_decref(jsonArray);
                return false;
                }
                
                countryArray->countries[i].languages.strings[j] = (char*)calloc(50, sizeof(char));
                strncpy(countryArray->countries[i].languages.strings[j], json_string_value(buffer), strlen(json_string_value(buffer))+1);
                (countryArray->countries[i].languages.count)++;
                iter = json_object_iter_next(languages, iter);
            }

            for(j = 0; j < (int)json_array_size(borders); j++) {
                buffer = json_array_get(borders, j);
                
                if(!json_is_string(buffer)) {
                printf("error: commit %d: borders buffer is not a string\n", i+1);
                json_decref(jsonArray);

                // free the malloc of languages before exiting
                for(i = 0; i < countryArray->count; i++) 
                    for(j = 0; j < countryArray->countries[i].languages.count; j++)
                        free(countryArray->countries[i].languages.strings[j]);

                return false;
                }

                countryArray->countries[i].borders.strings[j] = (char*)calloc(50, sizeof(char));
                strncpy(countryArray->countries[i].borders.strings[j], json_string_value(buffer), strlen(json_string_value(buffer))+1);
                (countryArray->countries[i].borders.count)++;
            }
            
            countryArray->count++;
    }

    json_decref(jsonArray);
    
    return true;

}

void stringArrayInit(struct stringArray *_stringArray) {
    _stringArray->count = 0;
}

void countryArrayInit(struct countryArray *_countryArray) {
    _countryArray->count = 0;
    int i;
    for(i = 0; i < 250; i++) {
        _countryArray->countries[i].languages.count = 0;
        _countryArray->countries[i].borders.count = 0;
    }
}

void countryArrayDelete(struct countryArray *_countryArray) {
    int i, j;
    for(i = 0; i < _countryArray->count; i++) {
        for(j = 0; j < _countryArray->countries[i].languages.count; j++)
            free(_countryArray->countries[i].languages.strings[j]);
        for(j = 0; j < _countryArray->countries[i].borders.count; j++)
            free(_countryArray->countries[i].borders.strings[j]);
    }
}
