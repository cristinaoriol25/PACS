
import argparse
import pandas as pd
import matplotlib.pyplot as plt

def main(args):
    df  = pd.read_csv(args.log, sep=" ")
    print(df)
    # etc.

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument('-l', '--log', help='log',
                        type=str, default="log/comparison.log")

    args = parser.parse_args()
    main(args)
