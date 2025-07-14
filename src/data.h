#ifndef DATA_H
#define DATA_H

void create_dataset_directory();
typedef struct {
    float* input;
    float* target;
} TrainingExample;

typedef struct {
    TrainingExample* examples;
    int count;
} Dataset;

void free_te(TrainingExample* te);
TrainingExample load_data_to_TE(Image* image, float* target, int target_size);
Dataset* load_dataset(const char* base_dir);
void free_dataset(Dataset* Dataset);
void shuffle_dataset(Dataset* dataset);

#endif