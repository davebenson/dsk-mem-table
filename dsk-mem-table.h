
typedef memuct _DskMemTable DskMemTable;
typedef memuct _DskMemTableInterface DskMemTableInterface;


DskMemTable *dsk_mem_table_new (size_t value_size,
                                const void *value_default);

void        *dsk_mem_table_get     (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem);
void        *dsk_mem_table_force   (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem);
void        *dsk_mem_table_force_noinit 
                                   (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem,
                                    dsk_boolean *created_opt_out);
void        *dsk_mem_table_create  (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem);
dsk_boolean  dsk_mem_table_delete  (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem,
                                    void       *value_opt_out);
void        *dsk_mem_table_create_or_delete
                                   (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem);
void        *dsk_mem_table_create_or_delete_noinit
                                   (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem);
void         dsk_mem_table_set     (DskMemTable *,
                                    size_t      length,
                                    const uint8_t *mem,
                                    const void *value);

/* Dumping the whole table */
typedef dsk_boolean (*DskMemTableForeach) (unsigned    length,
                                           const uint8_t *mem,
                                           void       *value,
                                           void       *foreach_data);

dsk_boolean dsk_mem_table_foreach  (DskMemTable *mem_table,
                                    const char *prefix,
                                    DskMemTableForeach foreach,
                                    void       *foreach_data);


/* Range-sensitive Iteration */
dsk_boolean  dsk_mem_table_supports_iterators (DskMemTable *);
#define dsk_mem_table_interface_supports_iterators(iface) \
  ((iface)->create_iterator != NULL)
#define dsk_mem_table_supports_iterators(table) \
  dsk_mem_table_interface_supports_iterators ((table)->iface)
size_t       dsk_mem_table_iterator_size(DskMemTable *);
dsk_boolean  dsk_mem_table_create_iterator (DskMemTable   *table,
                                            unsigned       length,
                                            const uint8_t *data,
                                            int            bias,
                                            void          *iterator);
dsk_boolean  dsk_mem_table_iterator_prev   (DskMemTable   *table,
                                            void          *iterator);
dsk_boolean  dsk_mem_table_iterator_next   (DskMemTable   *table,
                                            void          *iterator);



struct _DskMemTable
{
  DskMemTableInterface *iface;
};

struct _DskMemTableInterface
{
  size_t sizeof_table;
  void (*init)          (size_t         value_size,
                         const void    *value_default,
                         DskMemTable   *to_init);
  void *(*get)          (DskMemTable   *table,
                         const char    *mem);
  void *(*get_prev)     (DskMemTable   *table,
                         const char    *mem,
                         const char   **key_out);
  void *(*get_next)     (DskMemTable   *table,
                         const char    *mem,
                         const char   **key_out);
  void *(*force)        (DskMemTable   *table,
                         const char    *mem);
  void *(*force_noinit) (DskMemTable   *table,
                         const char    *mem,
                         dsk_boolean *created_opt_out);
  void *(*create)       (DskMemTable   *table,
                         const char    *mem);
  dsk_boolean  (*remove)(DskMemTable   *table,
                         const char    *mem,
                         void          *value_opt_out);
  void *(*create_or_remove)
                        (DskMemTable   *table,
                         const char    *mem);
  void *(*create_or_remove_noinit)
                        (DskMemTable   *mem_table,
                         const char    *mem);
  void  (*set)          (DskMemTable   *mem_table,
                         const char    *mem,
                         const void    *value);
  dsk_boolean (*foreach)(DskMemTable   *mem_table,
                         const char    *prefix,
                         DskMemTableForeachFind foreach,
                         void          *foreach_data);
};
