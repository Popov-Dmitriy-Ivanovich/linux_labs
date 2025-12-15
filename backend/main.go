package main

import (
    "fmt"
    "net/http"
	"os"
	"encoding/json"
)

type Config struct {
	Secret string `json:"secret"`
	Port string `json:"port"`
}

func main() {

	content, err := os.ReadFile("/config/config.json")
	if err != nil {
		panic(err.Error())
	}

	fmt.Println(string(content))
	var config Config

	err = json.Unmarshal(content, &config) 
	if err != nil {
		panic(err.Error())
	}

	content1, err1 := os.ReadFile("/build/output.txt")

	if err1 != nil {
		panic(err.Error())
	}

	fmt.Println(string(content1))
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        
		fmt.Println("got /")
		fmt.Fprintf(w, "%s \n %s \n", string(content1), config.Secret)
    })

    http.ListenAndServe(config.Port, nil)
}