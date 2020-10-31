"""
Note: the content of the movies from aforementioned playlist in README (7th August 2020)
is pretty deprecated, here I'm presenting code with removed deprecation warnings pytorch_lightning 1.0.4.
"""

import pdb
import multiprocessing

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
        self.cpu_count = multiprocessing.cpu_count()
        self.batch_size = 32

    def prepare_data(self):
        datasets.MNIST('data', train=True, download=True, transform=transforms.ToTensor())

    def setup(self, stage):
        dataset = datasets.MNIST('data', train=True, download=False, transform=transforms.ToTensor())
        self.train_data, self.val_data = random_split(dataset, [55000, 5000])

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
        return self._perform_step(batch)

    def validation_step(self, batch, batch_idx):
        results = self._perform_step(batch)
        results['val_acc'] = results['step_acc']
        del results['step_acc']
        return results

    def validation_epoch_end(self, val_step_outputs):
        avg_val_loss = torch.tensor([x['loss'] for x in val_step_outputs]).mean()
        avg_val_acc = torch.tensor([x['val_acc'] for x in val_step_outputs]).mean()
        self.log('val_loss', avg_val_loss, on_epoch=True, prog_bar=True, logger=True)
        self.log('avg_val_acc', avg_val_acc, on_epoch=True, prog_bar=True, logger=True)

    def train_dataloader(self):
        train_loader = DataLoader(self.train_data, batch_size=self.batch_size, num_workers=self.cpu_count)
        return train_loader

    def val_dataloader(self):
        val_loader = DataLoader(self.val_data, batch_size=self.batch_size, num_workers=self.cpu_count)
        return val_loader

    def _perform_step(self, batch):
        x, y = batch
        batch_size = x.size(0)
        x = x.view(batch_size, -1)
        logits = self(x)
        J = self.loss(logits, y)
        acc = accuracy(logits, y)
        return {'loss': J, 'step_acc': acc}


def main():
    model = ResidualNetwork()
    tb_logger = pl_loggers.TensorBoardLogger('logs/')
    trainer = pl.Trainer(max_epochs=5, gpus=1, logger=tb_logger)
    trainer.fit(model)

    return 0


if __name__ == "__main__":
    main()
