
import argparse
import pandas as pd
import matplotlib.pyplot as plt

def main(args):
    df  = pd.read_csv(args.log, sep=" ", header=0)
    df = df[['method', 'N', 'User(s)']]
    #print(df[df['method']=="sequential"]['N'])

    # plt.figure()

    # PLOT:
    fig, ax = plt.subplots()
    ax.scatter(x=df[df['method']=="sequential"]['N'], y=df[df['method']=="sequential"]['User(s)'], label="sequential")
    # ax.legend()

    ax.scatter(x=df[df['method']=="my_eigen_matmult"]['N'], y=df[df['method']=="my_eigen_matmult"]['User(s)'], label="eigen_vectorization")
    # ax.legend()

    ax.scatter(x=df[df['method']=="my_eigen_matmult_no_vect"]['N'], y=df[df['method']=="my_eigen_matmult_no_vect"]['User(s)'], label="eigen_no_vectorization")
    ax.legend()
    ax.set_xlabel("N")
    ax.set_ylabel("t (s)")
    ax.set_title("time - N for each method")
    ax.grid()
    plt.savefig('times.png')
    # etc.

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument('-l', '--log', help='log',
                        type=str, default="log/comparison.log")

    args = parser.parse_args()
    main(args)
