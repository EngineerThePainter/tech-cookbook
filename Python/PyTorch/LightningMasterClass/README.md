# PyTorch Lightning MasterClass

### Table of Contents

1. [Description](#description)
2. [Installation](#installation)
3. [Files](#files)
4. [Licensing, Authors, and Acknowledgements](#licensing)

## Description <a name="description"></a>

The code presented here is based on the
[PyTorch Lightning Masterclass](https://www.youtube.com/playlist?list=PLaMu-SDt_RB5NUm67hU2pdE75j6KaIOv2).

The code from the course was a bit old when I watched the movies (end of October 2020) as
PyTorch Lightning changed a bit since movies upload (August 2020). 
I really enjoyed these classes, so I've started working on the Lightning code to make it up to date with version 1.0.4 that 
was the latest in my pip.

## Installation <a name="installation"></a>

First you need to have Python and Pip installed either on your computer or in the virtual environment.
Then to install all requirements just type from this project directory:

```pip install -r requirements.txt```

Both script files are standalone, you can run them as normal Python scripts.
Keep in mind that they'll download the MNIST dataset to your local machine (under ```data``` directory)
and Lightning script will create additional ```logs``` directory where all logs from all experiments will go.

## Files <a name="files"></a>

The ```mnist_nn.py``` shows a classification neural network for MNIST dataset using PyTorch only, code is close to this
one presented in the movies with some small refactoring.

The ```mnist_nn_lightning.py``` is the same neural network model, but trained using the PyTorch Lightning. I was writing it to 
run it on the gpu.

## Licensing, Authors, and Acknowledgements <a name='licensing'></a>

I'm sharing this code under MIT License. 

The biggest thanks should go to the Alfredo Canziani and Willam Falcon who took effort to prepare the MasterClass - 
please watch [it](https://www.youtube.com/playlist?list=PLaMu-SDt_RB5NUm67hU2pdE75j6KaIOv2).

Big thanks should go to [Mick van Hulst](https://www.linkedin.com/in/mickvanhulst/), who shown me these classes in the first place.
