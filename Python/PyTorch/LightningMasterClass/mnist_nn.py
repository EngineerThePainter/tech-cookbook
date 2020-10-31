import pdb
import torch
from torch import nn
from torch import optim
from torch.utils.data import random_split, DataLoader

from torchvision import datasets, transforms


# More flexible model
class ResidualNetwork(nn.Module):
    def __init__(self):
        super().__init__()
        self.input_transformation = nn.Linear(28 * 28, 64)
        self.hidden_transformation = nn.Linear(64, 64)
        self.output_transformation = nn.Linear(64, 10)
        self.dropout = nn.Dropout(0.1)

    def forward(self, x):
        hidden_layer_1 = nn.functional.relu(self.input_transformation(x))
        hidden_layer_2 = nn.functional.relu(self.hidden_transformation(hidden_layer_1))
        # This plus applies dropout to both hidden layers
        drop_output = self.dropout(hidden_layer_2 + hidden_layer_1)
        logits = self.output_transformation(drop_output)
        return logits


def main():

    train_data = datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor())
    train, val = random_split(train_data, [55000, 5000])
    train_loader = DataLoader(train, batch_size=32)
    val_loader = DataLoader(val, batch_size=32)

    # Model
    model = nn.Sequential(
        # Input image is 28, by 28 pixels
        nn.Linear(28 * 28, 64),
        nn.ReLU(),
        nn.Linear(64, 64),
        nn.ReLU(),
        nn.Dropout(0.1),
        nn.Linear(64, 10)
    )

    model = ResidualNetwork()

    # Optimizer
    optimiser = optim.SGD(model.parameters(), lr=1e-2)

    # Define loss function
    loss = nn.CrossEntropyLoss()

    # Training loop
    nb_epochs = 5
    for epoch in range(nb_epochs):
        losses = list()
        accuracies = list()
        model.train()
        for batch in train_loader:
            x, y = batch

            # Reshape batch x channel x 28 x 28
            batch_size = x.size(0)
            x = x.view(batch_size, -1)

            # 1. Forward
            # logit = model(x) - for commented model
            logit = model.forward(x)
            # pdb.set_trace() # uncomment for debugging

            # 2. Compute the objective function
            J = loss(logit, y)

            # 3. Cleaning the gradient
            model.zero_grad()
            # params.grad.zero_()

            # 4. Compute the partial derivatives of j with respect to parameters
            J.backward()
            # params.grad.add_(dJ/dparams)

            # 5. step in the opposite direction of the gradient
            optimiser.step()
            # with torch.no_grad(): params - eta * params.grad

            losses.append(J.item())
            accuracies.append(y.eq(logit.detach().argmax(dim=1)).float().mean())

        print(f'Epoch {epoch + 1}')
        print(f'Train Loss: {torch.tensor(losses).mean():.2f}')
        print(f'Accuracy: {torch.tensor(accuracies).mean():.2f}')

        # Validation
        losses = list()
        accuracies = list()
        model.eval()
        for batch in val_loader:
            x, y = batch

            # Reshape batch x channel x 28 x 28
            batch_size = x.size(0)
            x = x.view(batch_size, -1)

            # 1. Forward
            with torch.no_grad():
                # logit = model(x) - for commented model
                logit = model.forward(x)

            # 2. Compute the objective function
            J = loss(logit, y)

            losses.append(J.item())
            accuracies.append(y.eq(logit.detach().argmax(dim=1)).float().mean())
        print(f'Val loss: {torch.tensor(losses).mean():.2f}')
        print(f'Val accuracy: {torch.tensor(accuracies).mean():.2f}')

    return 0


if __name__ == "__main__":
    main()
