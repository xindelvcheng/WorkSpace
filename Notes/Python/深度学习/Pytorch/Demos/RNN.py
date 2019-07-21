import torch
import torch.nn as nn

class RNN(nn.Module):
    def __init__(self,input_size,hidden_size,num_layers,num_classes):
        super(RNN,self).__init__()
        self.hidden_size = hidden_size
        self.num_layers = num_layers
        self.lstm = nn.LSTM(input_size,hidden_size,num_layers,batch_first=True)
        self.fc = nn.Linear(hidden_size,num_classes)

    def forward(self,x):
        h0 = torch.zeros(num_layers,batch_size,self.hidden_size)
        c0 = torch.zeros(num_layers,batch_size,self.hidden_size)

        out,_ = self.lstm(x,(h0,c0))
        out = self.fc(out[:,-1,:])
        return out

model = RNN(input_size,hidden_size,num_layers,num_classes).to(device)
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(),lr=learning_rate)

total_step = len(train_loader)
for epoch in range(num_epochs):
    for i,(images,labels) in enumerate(train_loader):
        images = images.reshape(-1,sequence_length,input_size).to(device)
        labels = labels.to(device)

        outputs = model(images)
        loss = criterion(outputs,labels)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()