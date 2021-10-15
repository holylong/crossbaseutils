package main

import (
	"fmt"
	. "io/ioutil"
	"os"
	"unsafe"
)

func findExt(path string, ext string) bool {
	finfo, _ := ReadDir(path)
	for _, s := range finfo {
		if s.IsDir() && s.Name() == ext {
			return true
		}
	}
	return false
}

func readAll(path string, ext string) ([]string, []string) {
	var all_file, no_file []string
	finfo, _ := ReadDir(path)
	for _, s := range finfo {
		real_path := path + "\\" + s.Name()
		if findExt(real_path, ext) {
			//all_file = append(all_file, readAll(real_path)...)
			all_file = append(all_file, real_path)
		} else if s.IsDir() {
			//fmt.Println(s.Name(), " ", s.Size())
			no_file = append(no_file, real_path)
		}
	}
	return all_file, no_file
}

func dumpToFile(path string, no_file []string) {
	f, _ := os.Create(path)
	defer f.Close()
	for _, data := range no_file {
		if len(data) > 0 {
			//f.Write(str2bytes(data))
			f.WriteString(data)
			f.WriteString("\n")
		}
	}
}

func str2bytes(s string) []byte {
	x := (*[2]uintptr)(unsafe.Pointer(&s))
	h := [3]uintptr{x[0], x[1], x[1]}
	return *(*[]byte)(unsafe.Pointer(&h))
}

func bytes2str(b []byte) string {
	return *(*string)(unsafe.Pointer(&b))
}

func main() {
	fmt.Println("caverge enter")
	args := os.Args
	if args == nil || len(args) < 2 {
		fmt.Println("error! please input argments !! caverge path ext")
		return
	}
	dpath := args[1]
	ext := args[2]
	fmt.Printf("input arguments %s %s\n", dpath, ext)
	var path string = string(dpath)
	all_file, no_file := readAll(path, ext)
	// for _, data := range all_file {
	// 	if len(data) > 0 {
	// 		fmt.Println(data)
	// 	}
	// }
	dumpToFile("a.txt", all_file)
	fmt.Println("---------------------------")
	// for _, data := range no_file {
	// 	if len(data) > 0 {
	// 		fmt.Println(data)
	// 	}
	// }

	dumpToFile("b.txt", no_file)
	fmt.Println("caverge exit")
}
