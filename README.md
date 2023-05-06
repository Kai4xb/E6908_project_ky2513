# E6908_project
This Project is about basketabll shooting detection. 
****
****
Data Collecting Folder contains Arduino ino file that for collecting data. 
****
Datasets Folder contains two datasets csv files: Correcr and Incorrect Dataset.
****
LSTM_Shot.ipynb file is how we preprocess the datasets, design and train the model, and convert the model form for hardware. Shot.ipynb file is a model without LSTM layer. It's the initial attempt for the final system design. The Shot.ipynb file can be ignored.
****
Prediction_Arduino Folder contains the ino file with model.h file. With these, Arduino hardware can make prediction for our shot position.
****
Python Folder contains a py file that generate the sound we need. Also, the sound wav file is in this folder as well.
