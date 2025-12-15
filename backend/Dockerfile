FROM golang:alpine AS builder
WORKDIR /goserv
COPY . .
RUN go build main.go

CMD ["./main"]