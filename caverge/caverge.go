package main

import (
	"fmt"

	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
)

func main() {
	fmt.Println("caverge enter")

	a := app.New()
	w := a.NewWindow("hello world")

	hello := widget.NewLabel("Hello Fyne.IO")
	editline := widget.NewRichTextWithText("i am caverge")
	w.SetContent(container.NewVBox(
		hello,
		editline,
		widget.NewButton("Hi", func() {
			hello.SetText("WelCome")
		}),
	))

	w.ShowAndRun()
}
