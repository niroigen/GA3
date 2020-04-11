# How to run programs

# Requirements
## Docker
Install docker here https://docs.docker.com/install/

## Creating docker image
### Step 1: Build the docker image
NOTE: Make sure you are on the root directory

To build the image, perform the following command 
`docker build . -t asn3`

### Step 2: Run the docker container
To run the container on your system run the following command
`docker run --rm -v ${PWD}:/app -it asn2 /bin/bash`

### Step 3: Head into the directory contiaing 
Once you are in the docker container, to head into the source code perform the following command
`cd app`



## Running Part 2
### Step 1: Jump into the build directory
To run the part 1 algorithm, you would have to go into the directory `build`

### Step 2: Prepare to create an executable using CMAKE
Next you would need to build the project using CMAKE
`cmake ..`

### Step 3: Create an executable for Part 1
Now you would have to create the executable file
`make`

### Step 4: Run program
`./ASN3/ASN3`