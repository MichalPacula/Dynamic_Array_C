#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 8

typedef struct {
  size_t size;
  size_t capacity;
  int *array;
} DynamicArray;

void array_init(DynamicArray **arrPtr) {
  DynamicArray *container;
  container = (DynamicArray *)malloc(sizeof(DynamicArray));

  if (container == NULL) {
    printf("Memory allocation failed\n");
    exit(0);
  }

  container->size = 0;
  container->capacity = INITIAL_SIZE;
  container->array = (int *)malloc(INITIAL_SIZE * sizeof(int));

  if (container->array == NULL) {
    printf("Memory allocation failed\n");
    exit(0);
  }

  *arrPtr = container;
}

void free_array(DynamicArray *container) {
  free(container->array);
  free(container);
}

void insert_item(DynamicArray *container, int item) {
  if (container->size == container->capacity) {
    int *temp = container->array;
    container->capacity *= 2;
    container->array = (int *)realloc(container->array, container->capacity * sizeof(int));
    if (container->array == NULL) {
      printf("Out of memory\n");
      container->array = temp;
      return;
    }
  }
  container->array[container->size++] = item;
}

int get_item(DynamicArray *container, size_t index) {
  if (index >= container->size) {
    printf("Index out of bounds\n");
    return -1;
  }
  return container->array[index];
}

void update_item(DynamicArray *container, size_t index, int item) {
  if (index >= container->size) {
    printf("Index out of bounds\n");
    return;
  }
  container->array[index] = item;
}

void print_array(DynamicArray *container) {
  printf("Array elements: ");
  for (size_t i = 0; i < container->size; i++) {
    printf("%d ", container->array[i]);
  }
  printf("\nSize: %zu", container->size);
  printf("\nCapacity: %zu\n", container->capacity);
}

void delete_item(DynamicArray *container, size_t index) {
  if (index >= container->size) {
    printf("Index out of bounds\n");
    return;
  }

  for (size_t i = index; i < container->size; i++) {
    container->array[i] = container->array[i+1];
  }
  container->size--;
}

int main() {
  DynamicArray *arr;
  array_init(&arr);

  for (size_t i = 0; i < 6; i++) {
    insert_item(arr, i + 11);
  }

  print_array(arr);
  printf("Third index: %d\n", get_item(arr, 3));
  delete_item(arr, 3);
  print_array(arr);
  printf("Third index: %d\n", get_item(arr, 3));

  for (size_t i = 0; i < 15; i++) {
    insert_item(arr, i + 17);
  }

  print_array(arr);

  free_array(arr);

  return 0;
}
