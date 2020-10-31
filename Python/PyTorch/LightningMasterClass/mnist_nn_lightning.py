"""
Note: the content of the movies from aforementioned playlist in README (7th August 2020)
is pretty deprecated, here I'm presenting code with removed deprecation warnings pytorch_lightning 1.0.4
"""

import pdb
import torch
from torch import nn
from torch import optim
from torch.utils.data import DataLoader, random_split

from torchvision import datasets, transforms
from pytorch_lightning import loggers as pl_loggers

import pytorch_lightning as pl
from pytorch_lightning.metrics.functional import accuracy

print(torch.cuda.current_device())
print(torch.cuda.device(0))
print(torch.cuda.device_count())
print(torch.cuda.get_device_name(0))
print(torch.cuda.is_available())


class ResidualNetwork(pl.LightningModule):
    def __init__(self):
        super().__init__()
        self.input_transformation = nn.Linear(28 * 28, 64)
        self.hidden_transformation = nn.Linear(64, 64)
        self.output_transformation = nn.Linear(64, 10)
        self.dropout = nn.Dropout(0.1)
        self.loss = nn.CrossEntropyLoss()

    def forward(self, x):
        hidden_layer_1 = nn.functional.relu(self.input_transformation(x))
        hidden_layer_2 = nn.functional.relu(self.hidden_transformation(hidden_layer_1))
        # This plus applies dropout to both hidden layers
        drop_output = self.dropout(hidden_layer_2 + hidden_layer_1)
        logits = self.output_transformation(drop_output)
        return logits

    def configure_optimizers(self):
        optimizer = optim.SGD(self.parameters(), lr=1e-2)
        return optimizer

    def training_step(self, batch, batch_idx):
        x, y = batch
        batch_size = x.size(0)
        x = x.view(batch_size, -1)
        logits = self(x)
        J = self.loss(logits, y)
        acc = accuracy(logits, y)
        pbar = {'train_acc': acc}
        return {'loss': J, 'progress_bar': pbar}

    def validation_step(self, batch, batch_idx):
        results = self.training_step(batch, batch_idx)
        results['progress_bar']['val_acc'] = results['progress_bar']['train_acc']
        del results['progress_bar']['train_acc']
        return results

    def validation_epoch_end(self, val_step_outputs):
        avg_val_loss = torch.tensor([x['loss'] for x in val_step_outputs]).mean()
        avg_val_acc = torch.tensor([x['progress_bar']['val_acc'] for x in val_step_outputs]).mean()
        self.log('val_loss', avg_val_loss)
        self.log('avg_val_acc', avg_val_acc)

    def train_dataloader(self):
        train_data = datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor())
        train, val = random_split(train_data, [55000, 5000])
        train_loader = DataLoader(train, batch_size=32)
        return train_loader

    def val_dataloader(self):
        train_data = datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor())
        train, val = random_split(train_data, [55000, 5000])
        val_loader = DataLoader(val, batch_size=32)
        return val_loader


class ImageClassifier(nn.Module):
    def __init__(self):
        self.resnet = ResidualNetwork()
        self.fc = nn.Linear()


def main():
    model = ResidualNetwork()
    tb_logger = pl_loggers.TensorBoardLogger('logs/')
    trainer = pl.Trainer(max_epochs=5, gpus=1, logger=tb_logger)
    trainer.fit(model)

    return 0


if __name__ == "__main__":
    main()
