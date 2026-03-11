#!/usr/bin/env bats
# @author Michael Tessier, Chao-Jung (Julie) Wu

@test numberOfCountriesInAmericas {
 run bash -c "bin/tp2 --region americas | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "56" ]]
}

@test numberOfCountriesInAfrica {
 run bash -c "bin/tp2 --region africa | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "58" ]]
}

@test numberOfCountriesInOceania {
 run bash -c "bin/tp2 --region oceania | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "27" ]]
}

@test numberOfCountriesInAsia {
 run bash -c "bin/tp2 --region asia | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "50" ]]
}

@test numberOfCountriesInEurope {
 run bash -c "bin/tp2 --region europe | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "53" ]]
}

@test numberOfCountriesInEurope {
run bash -c "bin/tp2 | grep Name | uniq | wc -l"
 [[ "${lines[0]}" =~ "248" ]]
}

@test "Deafult single country with lowercase code" {
 run bin/tp2 --country can 
 [ "${lines[0]}" = "Name: Canada" ]
 [ "${lines[1]}" = "Code: CAN" ]
}

@test "Deafult single country with uppercase code" {
 run bin/tp2 --country CAN 
 [ "${lines[0]}" = "Name: Canada" ]
 [ "${lines[1]}" = "Code: CAN" ]
}

@test "Single country with all values" {
 run bin/tp2 --show-languages --show-capital --show-borders --country usa
 [ "${lines[0]}" = "Name: United States" ]
 [ "${lines[1]}" = "Code: USA" ]
 [ "${lines[2]}" = "Capital: Washington D.C." ]
 [ "${lines[3]}" = "Languages: English" ]
 [ "${lines[4]}" = "Borders: CAN, MEX" ]
}

@test "Invalid country code cax" {
 run bin/tp2 --country cax
 [ "$output" = "error: country code \"CAX\" not found" ]
}

@test "Invalid country code x" {
 run bin/tp2 --country x
 [ "$output" = "error: the length of country code is 3" ]
}

@test "Ambiguous argument --s" {
 run bin/tp2 --s
 [[ "${lines[0]}" =~ "'--s' is ambiguous" ]]
}

@test "Invalid argument --d" {
 run bin/tp2 --d 
 [ "${lines[0]}" = "bin/tp2: unrecognized option '--d'" ]
 [ "${lines[1]}" = "Usage:" ]
 [ "${lines[2]}" = "bin/tp2 [--help] [--output-format FORMAT] [--output-filename FILENAME] [--show-languages] [--show-capital] [--show-borders] [--show-flag] [--country COUNTRY] [--region REGION]" ]
}

@test "Invalid argument: combination of country and region" {
 run bin/tp2 --region americas --country can
 [ "${lines[0]}" = "Error, country and region cannot be specified at the same time." ]
}

@test "Invalid argument: mandatory filename for png" {
 run bin/tp2 --region americas --output-format png
 [ "${lines[0]}" = "Error, output filename is mandatory for the \"png\" format." ]
}

@test "Invalid argument: --show-flag in text format" {
 run bin/tp2 --show-flag
 [ "${lines[0]}" = "Error, show-flags is not valid for text format." ]
}

@test "Deafult region in lowercase" {
 run bin/tp2 --region oceania
 [ "${lines[0]}" = "Name: American Samoa" ]
 [ "${lines[1]}" = "Code: ASM" ]
 [ "${lines[2]}" = "Name: Australia" ]
 [ "${lines[3]}" = "Code: AUS" ]
 [ "${lines[4]}" = "Name: Cocos (Keeling) Islands" ]
 [ "${lines[5]}" = "Code: CCK" ]
 [ "${lines[6]}" = "Name: Cook Islands" ]
 [ "${lines[7]}" = "Code: COK" ]
 [ "${lines[8]}" = "Name: Christmas Island" ]
 [ "${lines[9]}" = "Code: CXR" ]
 [ "${lines[10]}" = "Name: Fiji" ]
 [ "${lines[11]}" = "Code: FJI" ]
 [ "${lines[12]}" = "Name: Micronesia" ]
 [ "${lines[13]}" = "Code: FSM" ]
 [ "${lines[14]}" = "Name: Guam" ]
 [ "${lines[15]}" = "Code: GUM" ]
 [ "${lines[16]}" = "Name: Kiribati" ]
 [ "${lines[17]}" = "Code: KIR" ]
 [ "${lines[18]}" = "Name: Marshall Islands" ]
 [ "${lines[19]}" = "Code: MHL" ]
 [ "${lines[20]}" = "Name: Northern Mariana Islands" ]
 [ "${lines[21]}" = "Code: MNP" ]
 [ "${lines[22]}" = "Name: New Caledonia" ]
 [ "${lines[23]}" = "Code: NCL" ]
 [ "${lines[24]}" = "Name: Norfolk Island" ]
 [ "${lines[25]}" = "Code: NFK" ]
 [ "${lines[26]}" = "Name: Niue" ]
 [ "${lines[27]}" = "Code: NIU" ]
 [ "${lines[28]}" = "Name: Nauru" ]
 [ "${lines[29]}" = "Code: NRU" ]
 [ "${lines[30]}" = "Name: New Zealand" ]
 [ "${lines[31]}" = "Code: NZL" ]
 [ "${lines[32]}" = "Name: Pitcairn Islands" ]
 [ "${lines[33]}" = "Code: PCN" ]
 [ "${lines[34]}" = "Name: Palau" ]
 [ "${lines[35]}" = "Code: PLW" ]
 [ "${lines[36]}" = "Name: Papua New Guinea" ]
 [ "${lines[37]}" = "Code: PNG" ]
 [ "${lines[38]}" = "Name: French Polynesia" ]
 [ "${lines[39]}" = "Code: PYF" ]
 [ "${lines[40]}" = "Name: Solomon Islands" ]
 [ "${lines[41]}" = "Code: SLB" ]
 [ "${lines[42]}" = "Name: Tokelau" ]
 [ "${lines[43]}" = "Code: TKL" ]
 [ "${lines[44]}" = "Name: Tonga" ]
 [ "${lines[45]}" = "Code: TON" ]
 [ "${lines[46]}" = "Name: Tuvalu" ]
 [ "${lines[47]}" = "Code: TUV" ]
 [ "${lines[48]}" = "Name: Vanuatu" ]
 [ "${lines[49]}" = "Code: VUT" ]
 [ "${lines[50]}" = "Name: Wallis and Futuna" ]
 [ "${lines[51]}" = "Code: WLF" ]
 [ "${lines[52]}" = "Name: Samoa" ]
 [ "${lines[53]}" = "Code: WSM" ]
}

@test "Deafult region in uppercase" {
 run bin/tp2 --region OCEANIA
 [ "${lines[0]}" = "Name: American Samoa" ]
 [ "${lines[1]}" = "Code: ASM" ]
 [ "${lines[2]}" = "Name: Australia" ]
 [ "${lines[3]}" = "Code: AUS" ]
 [ "${lines[4]}" = "Name: Cocos (Keeling) Islands" ]
 [ "${lines[5]}" = "Code: CCK" ]
 [ "${lines[6]}" = "Name: Cook Islands" ]
 [ "${lines[7]}" = "Code: COK" ]
 [ "${lines[8]}" = "Name: Christmas Island" ]
 [ "${lines[9]}" = "Code: CXR" ]
 [ "${lines[10]}" = "Name: Fiji" ]
 [ "${lines[11]}" = "Code: FJI" ]
 [ "${lines[12]}" = "Name: Micronesia" ]
 [ "${lines[13]}" = "Code: FSM" ]
 [ "${lines[14]}" = "Name: Guam" ]
 [ "${lines[15]}" = "Code: GUM" ]
 [ "${lines[16]}" = "Name: Kiribati" ]
 [ "${lines[17]}" = "Code: KIR" ]
 [ "${lines[18]}" = "Name: Marshall Islands" ]
 [ "${lines[19]}" = "Code: MHL" ]
 [ "${lines[20]}" = "Name: Northern Mariana Islands" ]
 [ "${lines[21]}" = "Code: MNP" ]
 [ "${lines[22]}" = "Name: New Caledonia" ]
 [ "${lines[23]}" = "Code: NCL" ]
 [ "${lines[24]}" = "Name: Norfolk Island" ]
 [ "${lines[25]}" = "Code: NFK" ]
 [ "${lines[26]}" = "Name: Niue" ]
 [ "${lines[27]}" = "Code: NIU" ]
 [ "${lines[28]}" = "Name: Nauru" ]
 [ "${lines[29]}" = "Code: NRU" ]
 [ "${lines[30]}" = "Name: New Zealand" ]
 [ "${lines[31]}" = "Code: NZL" ]
 [ "${lines[32]}" = "Name: Pitcairn Islands" ]
 [ "${lines[33]}" = "Code: PCN" ]
 [ "${lines[34]}" = "Name: Palau" ]
 [ "${lines[35]}" = "Code: PLW" ]
 [ "${lines[36]}" = "Name: Papua New Guinea" ]
 [ "${lines[37]}" = "Code: PNG" ]
 [ "${lines[38]}" = "Name: French Polynesia" ]
 [ "${lines[39]}" = "Code: PYF" ]
 [ "${lines[40]}" = "Name: Solomon Islands" ]
 [ "${lines[41]}" = "Code: SLB" ]
 [ "${lines[42]}" = "Name: Tokelau" ]
 [ "${lines[43]}" = "Code: TKL" ]
 [ "${lines[44]}" = "Name: Tonga" ]
 [ "${lines[45]}" = "Code: TON" ]
 [ "${lines[46]}" = "Name: Tuvalu" ]
 [ "${lines[47]}" = "Code: TUV" ]
 [ "${lines[48]}" = "Name: Vanuatu" ]
 [ "${lines[49]}" = "Code: VUT" ]
 [ "${lines[50]}" = "Name: Wallis and Futuna" ]
 [ "${lines[51]}" = "Code: WLF" ]
 [ "${lines[52]}" = "Name: Samoa" ]
 [ "${lines[53]}" = "Code: WSM" ]
}

@test "Invalid region" {
 run bin/tp2 --region Oceanix
 [ "$output" = "error: region name \"Oceanix\" not found" ]
}

@test "Help argument" {
 run bin/tp2 --help
 [ "${lines[0]}" = "Usage:" ]
 [ "${lines[1]}" = "bin/tp2 [--help] [--output-format FORMAT] [--output-filename FILENAME]" ]
 [ "${lines[2]}" = " [--show-languages] [--show-capital] [--show-borders] [--show-flag]" ]
 [ "${lines[3]}" = " [--country COUNTRY | --region REGION]" ]
 [ "${lines[4]}" = "Displays information about countries." ]
 [ "${lines[5]}" = "Optional arguments:" ]
 [ "${lines[6]}" = "  --help                     Show this help message and exit." ]
 [ "${lines[7]}" = "  --output-format FORMAT     Selects the ouput format (either \"text\", \"dot\" or \"png\")." ]
 [ "${lines[8]}" = "                             The \"dot\" format is the one recognized by Graphviz." ]
 [ "${lines[9]}" = "                             The default format is \"text\"." ]
 [ "${lines[10]}" = "  --output-filename FILENAME The name of the output filename. This argument is" ]
 [ "${lines[11]}" = "                             mandatory for the \"png\" format. For the \"text\" and \"dot\"" ]
 [ "${lines[12]}" = "                             format, the result is printed on stdout if no output" ]
 [ "${lines[13]}" = "                             filename is given." ]
}



