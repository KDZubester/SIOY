# Instructions for Downloading and Setting Up Arduino Program and GitHub Files
Hello future engineers! We are excited to share this fun engineering project with you! These instructions will guide you on your first steps to changing the world with your skills and ideas. In preparation to create your own DIY Digital Watch, you will learn how to set up the coding environment you will use to control an Arduino and how to get your first program to run. There are three main sections to these instructions: (1) downloading the Arduino program; (2) downloading the GitHub files; (3) compiling the Arduino code needed to begin the DIY Digital Watch project. This process should take no more than 20 minutes. So let's get started!

## Materials required:
These instructions are meant for **WINDOWS** computers. If you are using a Linux or Mac, the user interface will look different.

## Downloading the Arduino Program

### Step 1
Go to this webpage: https://www.arduino.cc/en/software

### Step 2
Click on one of these three links to start the download. The link you need to click on will change depending on what type of computer you are using. 
![image](https://user-images.githubusercontent.com/63425135/226770371-410e9a71-cb2c-4d7d-b8db-c7cd933b3cf7.png)

### Step 3
Click the file once the download is complete to launch the installer.
![image](https://user-images.githubusercontent.com/63425135/226972112-4df4d514-8eda-491d-acc9-79fe1b5cd220.png)

### Step 4
Agree to Terms and Conditions 
![image (1)](https://user-images.githubusercontent.com/97060692/226774761-e1a90981-11a1-4aac-84a5-a397f853eb19.png)

### Step 5
Choose to install for a single user
![image (2)](https://user-images.githubusercontent.com/97060692/226774866-7d62e2af-11a7-437d-9fb7-413606e08a0c.png)

### Step 6
Accept default file location. But you can pick a location that better suits you if you want.
![image (3)](https://user-images.githubusercontent.com/97060692/226774965-4bf02f7d-7762-420f-83b5-cb4786660af1.png)

### Step 7
Complete installation and open the Arduino IDE
![image (4)](https://user-images.githubusercontent.com/97060692/226775143-bd63b124-2bf6-4072-9f55-3f3eba4c0e50.png)


## Downloading the GitHub files

### Step 8
Open the GitHub repository and click on green button that says "Code"
![image](https://user-images.githubusercontent.com/63425135/226771511-e568b523-3d27-42c8-b512-804fc9b7fee8.png)

### Step 9
Click "Download Zip" from the dropdown menu that appeared
![image](https://user-images.githubusercontent.com/63425135/226771765-abfcf85e-16ef-4540-87b2-27067f0453cb.png)

This will download a .zip file that contains all of the folders you will need for this project

### Step 10
Click the carrot symbol on the icon that appeared on the bottom left of your window.
![image](https://user-images.githubusercontent.com/63425135/226771989-ae3a51ec-529b-442b-af1e-81303c110482.png)

### Step 11
Choose the "Show in Folder" option.
![image](https://user-images.githubusercontent.com/63425135/226772040-52b03f58-548c-4bb5-a41e-e768be659d3e.png)

Clicking on that option will take you to the location of where that .zip folder was downloaded to. You can change the location of where you want this folder to be so it is easier to find later.
![image](https://user-images.githubusercontent.com/63425135/226773381-eeb3bc1d-a67d-49cc-bb3c-6f86ddce9e83.png)

### Step 12
Right click on the folder to make an options menu appear.
![image](https://user-images.githubusercontent.com/63425135/226772311-7fce53dc-5bc2-450c-b52a-d0e4db331b89.png)

### Step 13
Select "Extract All".
![image](https://user-images.githubusercontent.com/63425135/226772425-2f1e9532-07bd-4a5d-8438-c006897b0cc7.png)

This will allow you to fully access the data inside of the .zip folder

### Step 14
Select the location for the computer to send the unzipped folder to.
If you have not already picked an easy place to find the folder for later use, please do so now. **We will need to access and change some of the files you just downloaded. So, it is very important that you know where they are!**

Once the computer is done extracting the data from the folder, it will take you inside the newly unzipped folder.

### Step 15
Double click on "Self-Starter-Kits-main" to enter the folder
![image](https://user-images.githubusercontent.com/63425135/226772847-c318fcc4-3718-4497-85bd-0704b9bd929e.png)

There is a lot of stuff inside the folder. You can explore and use it however you want.

### Step 16
Double click on the folder titled, "Watch_02.1"
![image](https://user-images.githubusercontent.com/63425135/226773092-0b2b55e0-8ddb-4c9f-9dcc-61c9e03cfbec.png)

This folder has all of the code that the DIY Digital Watch will need to run.

### Step 17
Double click on the file named "Watch_02.1.ino"
![image](https://user-images.githubusercontent.com/63425135/226773203-bd785b97-69db-4794-aa57-bc6bd58d8a77.png)

This will open the Arduino project in the Arduino Program


## Compiling Arduino Code for the first time

### Step 18
Click Tools and then hover over the "Board" setting, then "Arduino AVR boards", then select "Arduino Nano" to select the type of board we will be using
![image](https://user-images.githubusercontent.com/97060692/227098797-51ac0d71-367a-4861-935f-7cb1b7a8c575.png)

### Step 19
Click "Tools" and then hover over the "Processor" setting, then select "ATMega328P (Old Bootloader)" to choose the processor
![image](https://user-images.githubusercontent.com/97060692/227099233-aafdd835-bce3-4063-a8e5-4a4d94eb7ceb.png)

### Step 20
Click the Verify button (blue checkmark) to compile program
![image (5)](https://user-images.githubusercontent.com/97060692/226983691-987cdcde-3dc5-4bd3-ab11-c875d8c46434.png)

Compilation errors will be reported in the output window
![image (6)](https://user-images.githubusercontent.com/97060692/226984462-8e9e4500-bdd5-471e-aec4-aa33e5c208ae.png)
**NOTE:** Most users will be missing the libraries required for the watch code to run correctly. So, the compilation will most likely fail. **This is expected at this point.** We will now grab the libraries we need and put them into the Arduino program.

### Step 21
Open two File Explorer windows side-by-side 

### Step 22
Click on "This PC" in each window
![image](https://user-images.githubusercontent.com/97060692/226994200-30a1c028-59f0-45dd-bf77-edd137de9f38.png)

### Step 23 
Search for "libraries" in both windows and select "libraries - Arduino" in one, and "libraries - Self-Starter-Kits-main" in the other
![image](https://user-images.githubusercontent.com/97060692/226994293-a6f99868-0cdf-4973-93e3-5c167539a3d9.png)

This is what you should see in the two windows
![image](https://user-images.githubusercontent.com/97060692/226996576-00003dab-dd80-449d-96a8-c08c140147dd.png)

### Step 24
Copy everything in the "libraries - Self-Starter-Kits-main" folder except the readme.txt file
![image](https://user-images.githubusercontent.com/97060692/226996631-ae66f923-edbc-4545-aff2-f39477de7567.png)

### Step 25
Paste those folders into the "libraries - Arduino" folder
![image](https://user-images.githubusercontent.com/97060692/226996691-b9582f36-b0ea-4824-9163-0b74be607565.png)

This is what you should now see in the two windows
![image](https://user-images.githubusercontent.com/97060692/226996795-01627129-c33d-4b5e-a5e3-557b7ca6e7b3.png)

### Step 26
Go back to the Arduino program and press the compile button again. The output should show all white text and give information about how many bytes the sketch uses.
![image](https://user-images.githubusercontent.com/97060692/226996853-33c220dd-5a86-4631-82b6-caee11035c03.png)


## What if the Arduino program still shows errors???

Do not worry if the Arduino program still won't compile. All you need to do is follow these steps to manually download the necessary libraries.

Missing libraries will cause errors in the Output window.  
![image](https://user-images.githubusercontent.com/97060692/227089647-455b3175-59ef-4b4d-83b3-136f7a8384a0.png)

Open the Library Manager by clicking the book icon on the left side of the screen
![image](https://user-images.githubusercontent.com/97060692/227089750-01aca051-a28d-4d34-a479-958ea7e5cf2c.png)

Search for the missing library
![image](https://user-images.githubusercontent.com/97060692/227089954-b4d9b1b2-d35b-4680-ab92-371a4f4a695d.png)

Choose the library you are looking for and click "Install"
**NOTE:** If the install button is not visible, expand the Library Manager window
**NOTE:** If it is not clear which library to install, googling the .h file that throws an error will be helpful
![image](https://user-images.githubusercontent.com/97060692/227090402-fb368dc7-b31a-4cb8-8626-7158554aac20.png)

