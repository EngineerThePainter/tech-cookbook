# PyTorch Lightning MasterClass

### Table of Contents

1. [Description](#description)
2. [Installation](#installation)
3. [Licensing, Authors, and Acknowledgements](#licensing)

## Description <a name="description"></a>

The work presented here is taken from the 
[PyTorch Lightning Masterclass](https://www.youtube.com/playlist?list=PLaMu-SDt_RB5NUm67hU2pdE75j6KaIOv2).

The code from the course was a bit old when I took watched the movies (end of October 2020).
The PyTorch Lightning changed a bit since movies upload (August 2020). 
I really enjoyed these classes, so I've started working on the Lightning code to make it up to date with version 1.0.4
of the PyTorch Lightning.

## Installation <a name="description"></a>

First you need to have a Python and pip installed on your computer or have virtual environment ready.
Then to install all requirements just type from this project directory:

```pip install -r requirements.txt```

Both script files are standalone, you can run them as normal Python scripts.
Keep in mind that they'll download the MNIST dataset to your local machine (under ```data``` directory)
and Lightning script will create additional ```logs``` directory where all logs from all experiments will go. 

## Licensing, Authors, and Acknowledgements <a name='licensing'></a>

I'm sharing this code under MIT License. 

The biggest thanks should go to the Alfredo Canziani and Willam Falcon who took effort to prepare the MasterClass - 
you must watch [it](https://www.youtube.com/playlist?list=PLaMu-SDt_RB5NUm67hU2pdE75j6KaIOv2) in order to understand
what happens here if you are not familiar with the PyTorch.

Also a big thanks should go to Mick van Hulst, who shown me these classes in the first place.